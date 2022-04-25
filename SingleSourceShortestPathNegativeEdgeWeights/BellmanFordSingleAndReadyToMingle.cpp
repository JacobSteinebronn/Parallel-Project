#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = 1e18;

int numNodes, numEdges, sourceNode;
vector<tuple<int, int, ll>> edges;
vector<vector<pair<int, ll>>> adjEdges;

vector<ll> dist;

vector<ll> getDistances(){
    dist = vector<ll>(numNodes, INF);

    dist[sourceNode] = 0;

    for(int iteration = 0; iteration < numNodes - 1; ++iteration){
        for(auto [u, v, w] : edges){
            if(dist[u] < INF && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
            }
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

    return dist;
}

int main(){
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
