#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll BIG = 1e18;

// default value of numThreads
int numThreads = 10;

int numNodes, numEdges, sourceNode;
vector<tuple<int, int, ll>> edges;

vector<ll> dist;
vector<mutex*> locks;

void doThreadStuff(int startEdge, int endEdge){
    for(int edgeID = startEdge; edgeID <= endEdge; ++edgeID){
        auto [u, v, w] = edges[edgeID];

        locks[u]->lock();
        locks[v]->lock();

        dist[v] = min(dist[v], dist[u] + w);

        locks[u]->unlock();
        locks[v]->unlock();
    }
}

vector<ll> getDistances(){
    dist = vector<ll>(numNodes, BIG);
    locks = vector<mutex*>(numNodes);

    for(int node = 0; node < numNodes; ++node){
        locks[node] = new mutex();
    }

    dist[sourceNode] = 0;

    int numHandledByEachThread = numEdges / numThreads;

    for(int iteration = 0; iteration < numNodes - 1; ++iteration){
        vector<thread*> threads(numThreads);

        for(int threadIdx = 0; threadIdx < numThreads; ++threadIdx){
            int startEdge = numHandledByEachThread * threadIdx;
            int endEdge = numHandledByEachThread * threadIdx + numHandledByEachThread - 1;

            endEdge = min(endEdge, numEdges - 1);

            threads[threadIdx] = new thread(doThreadStuff, startEdge, endEdge);
        }

        for(int threadIdx = 0; threadIdx < numThreads; ++threadIdx){
            threads[threadIdx]->join();
        }
    }

    return dist;
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
    for(int edgeID = 0; edgeID < numEdges; ++edgeID){
        int u, v;
        ll w;

        cin >> u >> v >> w;
        --u, --v;

        edges[edgeID] = {u, v, w};
    }

    vector<ll> dist = getDistances();

    for(int node = 0; node < numNodes; ++node){
        cout << node << ": " << dist[node] << "\n";
    }

    return 0;
}