dist[sourceNode] = 0;
for(int i = 0; i < numNodes - 1; ++i){
   for(auto [u, v, w] : edges){
       if(dist[u] < INF && dist[u] + w < dist[v]){
           dist[v] = dist[u] + w;
       }
   }
}