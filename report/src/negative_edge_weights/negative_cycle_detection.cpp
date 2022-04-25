queue<int> q;
vector<bool> marked(numNodes);
for(auto [u, v, w] : edges){
    if(!marked[v] && dist[u] < INF && dist[u] + w < dist[v]){
        marked[v] = true;
        dist[v] = -INFINITY;
        q.push(v);
    }
}

while(!q.empty()){
    int u = q.front();
    q.pop();
    
    for(auto [v, w] : adjEdges[u]){
        if(!marked[v]){
            marked[v] = true;
            dist[v] = -INFINITY;
            q.push(v);
        }
    }
}