#include <bits/stdc++.h>

using namespace std;

class ConcurrentDisjointSetUnionLinkByIndexAndSplitting {
private:
  mutable vector<atomic<int>> parent;

public:

  ConcurrentDisjointSetUnionLinkByIndexAndSplitting(int nodes): parent(nodes) {
    for(int i = 0; i < nodes; i++) {
      int value = (int) i;
      parent[i] = value;
    }
  }

  int find(int x) const {
    int u = x;
    int v = parent[u];
    int w = parent[v];

    while(v != w) {
      parent[u].compare_exchange_weak(v, w);

      v = parent[u];
      w = parent[v];

      parent[u].compare_exchange_weak(v, w);

      u = v;
      v = parent[u];
      w = parent[v];
    }

    return v;
  }

  void link(int u, int v) {
    if(u < v) {
      parent[u].compare_exchange_weak(u, v);
    } else {
      parent[v].compare_exchange_weak(v, u);
    }
  }

  void unite(int x, int y) {
    int u = find(x);
    int v = find(y);

    while(u != v) {
      link(u, v);
      u = find(u);
      v = find(v);
    }
  }

  bool sameSet(int x, int y) {
    int u = find(x);
    int v = find(y);

    while(u != v) {
      int w = parent[u];
      if(u == w) return false;
      u = find(u);
      v = find(v);
    }
    return true;
  }

};

// our concurrent disjoint set union
const int N = 20;
const int NUM_THREADS = 12;

ConcurrentDisjointSetUnionLinkByIndexAndSplitting cdsu(N);

// <operation, x, y>
using Query = tuple<string, int, int>;

void runThroughQueries(int threadID, vector<Query> queries) {
  vector<bool> results;
  for(auto& [operation, x, y] : queries) {
    if(operation == "UNITE") {
      cdsu.unite(x, y);
      results.push_back(false);
    }
    if(operation == "SAMESET") {
      results.push_back(cdsu.sameSet(x, y));
    }
  }
}

int main() {
  srand(time(0));
  
  vector<vector<Query>> allQueries(NUM_THREADS);

  const int M = 10 * NUM_THREADS;
  for(int i = 0; i < NUM_THREADS; i++) {
    for(int j = 0; j < (M / NUM_THREADS); j++) {
      int operationID = rand() % 2;
      int x = rand() % N;
      int y = rand() % N;
      
      string operation = operationID ? "UNITE" : "SAMESET";
      allQueries[i].emplace_back(operation, x, y);
    }
  }

  vector<thread> threads;
  for(int i = 0; i < NUM_THREADS; i++) {
    threads.push_back(thread(runThroughQueries, i, allQueries[i]));
  }

  for(int i = 0; i < NUM_THREADS; i++) {
    threads[i].join();
  }

  return 0;
}
