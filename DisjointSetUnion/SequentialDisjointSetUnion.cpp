#include <bits/stdc++.h>

using namespace std;

class DisjointSetUnion {
  private:
    vector<int> parents;
    vector<int> sizes;

  public:
    DisjointSetUnion(int nodes): parents(nodes), sizes(nodes) {
      for(int i = 0; i < nodes; i++) {
        parents[i] = i;
        sizes[i] = 1;
      }
    }

    // find the representative of x
    int find(int x) {
      if(parents[x] == x) {
        return x;
      }

      // compression
      parents[x] = find(parents[x]);
      return parents[x];
    }

    // combine the sets that contain x and y
    // returns true if the sets are successfully unioned
    bool unite(int x, int y) {
      x = find(x);
      y = find(y);
      
      if(x != y) {
        if(sizes[x] < sizes[y]) {
          parents[x] = y;
          sizes[y] += sizes[x];
        } else {
          parents[y] = x;
          sizes[x] += sizes[y];
        }
        return true;
      }
      return false;
    }

    // determines if x and y are in the same set.
    bool sameSet(int x, int y) {
      x = find(x);
      y = find(y);
      return x == y;
    }
};

int main() {
  srand(time(0));

  int n = 30;
  int m = 100;

  DisjointSetUnion dsu(n);

  for(int ops = 0; ops < m; ops++) {
    int operationsID = rand() % 2;
    int x = rand() % n;
    int y = rand() % n;
    // unite
    if(operationsID == 0) {
      dsu.unite(x, y);
      cout << "unite(" << x << ", " << y << ")" << endl;
    } else { // same set
      bool result = dsu.sameSet(x, y);
      cout << "sameSet(" << x << ", " << y << ") = " << (result ? "TRUE" : "FALSE") << endl;
    }
  }

  return 0;
}
