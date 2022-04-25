void updateEdges(int startEdge, int endEdge){
    for(int edgeID = startEdge; edgeID < endEdge; ++edgeID){
        auto [u, v, w] = edges[edgeID];

        locks[u]->lock();
        locks[v]->lock();

        if(dist[u] < INF && dist[u] + w < dist[v]){
            dist[v] = dist[u] + w;
        }
        
        locks[u]->unlock();
        locks[v]->unlock();
    }
}