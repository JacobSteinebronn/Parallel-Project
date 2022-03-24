#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll BIG = 1e18;

int numNodes, numEdges, startNode;
vector<tuple<int, int, ll>> edges;

vector<ll> dist;

vector<ll> getDistances(){
    dist = vector<ll>(numNodes, BIG);

    dist[startNode] = 0;

    for(int iteration = 0; iteration < numNodes - 1; ++iteration){
        for(auto [u, v, w] : edges){
            dist[v] = min(dist[v], dist[u] + w);
        }
    }

    return dist;
}

int main(){
    cin >> numNodes >> numEdges;

    startNode = 0;

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