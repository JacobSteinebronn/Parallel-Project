void dijkstra(int s) {
   for(int i = 0; i < n; i++) res[s][i] = oo;
   set<pair<ll, int>> nxt;
   nxt.emplace(res[s][s] = 0, s);

   for(int i = 0; i < n; i++){
      auto [d, u] = *nxt.begin();
      nxt.erase(nxt.begin());
      // explore u's edges
      for(int v = 0; v < n; v++)
         if(res[s][v] > d + adj[u][v]) {
            nxt.erase(make_pair(res[s][v], v));
            res[s][v] =  d + adj[u][v];      
            nxt.emplace(make_pair(res[s][v], v));      
         }
   }
}