#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = 1e18;
const int MAX_NODES = 100'000;

// default value of numThreads
int numThreads = 10;

int numNodes, numEdges, sourceNode;
vector<tuple<int, int, ll>> edges;
vector<vector<pair<int, ll>>> adjEdges;

atomic<ll> dist[MAX_NODES];

void doThreadStuff(int startEdge, int endEdge){
    for(int edgeID = startEdge; edgeID < endEdge; ++edgeID){
        auto [u, v, w] = edges[edgeID];

        if(dist[u] < INF && dist[u] + w < dist[v]){
            dist[v] = dist[u] + w;
        }
    }
}

vector<ll> getDistances(){
    for(int i = 0; i < numNodes; ++i){
        dist[i] = INF;
    }

    dist[sourceNode] = 0;

    int numHandledByEachThread = numEdges / numThreads;

    for(int iteration = 0; iteration < numNodes - 1; ++iteration){
        vector<thread*> threads(numThreads);

        for(int threadIdx = 0; threadIdx < numThreads; ++threadIdx){
            int startEdge = numHandledByEachThread * threadIdx;
            int endEdge = numHandledByEachThread * (threadIdx + 1);

            endEdge = min(endEdge, numEdges);

            threads[threadIdx] = new thread(doThreadStuff, startEdge, endEdge);
        }

        for(int threadIdx = 0; threadIdx < numThreads; ++threadIdx){
            threads[threadIdx]->join();
        }
    }

    queue<int> q;
    vector<bool> marked(numNodes);
    for(auto [u, v, w] : edges){
        if(!marked[v] && dist[u] < INF && dist[u] + w < dist[v]){
            marked[v] = true;
            dist[v] = -INF;
            q.push(v);
        }
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(auto [v, w] : adjEdges[u]){
            if(!marked[v]){
                marked[v] = true;
                dist[v] = -INF;
                q.push(v);
            }
        }
    }

    vector<ll> out(numNodes);
    for(int i = 0; i < numNodes; ++i){
        out[i] = dist[i];
    }

    return out;
}

int main(int argc, char **argv){
    // we might want the second argument of our run to be the number of threads
    try {
        if(argc >= 2){
            string s = argv[1];
            numThreads = stoi(s);
        }
    }
    catch(...){}

    cin >> numNodes >> numEdges;

    sourceNode = 0;

    edges = vector<tuple<int, int, ll>>(numEdges);
    adjEdges = vector<vector<pair<int, ll>>>(numNodes);
    for(int edgeID = 0; edgeID < numEdges; ++edgeID){
        int u, v;
        ll w;

        cin >> u >> v >> w;
        --u, --v;

        edges[edgeID] = {u, v, w};
        adjEdges[u].emplace_back(v, w);
    }

    vector<ll> dist = getDistances();

    for(int node = 0; node < numNodes; ++node){
        cout << node << ": " << dist[node] << "\n";
    }

    return 0;
}