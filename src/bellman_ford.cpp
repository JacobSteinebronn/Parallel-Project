dist[sourceNode] = 0;
for(int i = 0; i < numNodes - 1; ++i){
   for(auto [u, v, w] : edges){
      dist[v] = min(dist[v], dist[u] + w);
   }
}