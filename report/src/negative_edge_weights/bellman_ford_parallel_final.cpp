atomic<int> numThreadsWorking(0);

void updateEdges(int startEdge, int endEdge){
    for(int iteration = 0; iteration < numNodes - 1; ++iteration){
        ++numThreadsWorking;

        for(int edgeID = startEdge; edgeID < endEdge; ++edgeID){
            auto [u, v, w] = edges[edgeID];

            if(dist[u] < INF && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                ++numUpdates;
            }
        }

        --numThreadsWorking;

        while(numThreadsWorking > 0);
    }
}