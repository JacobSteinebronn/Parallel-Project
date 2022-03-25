void dijkstra(int s) {
   for(int i = 0; i < n; i++) res[s][i] = oo;
   res[s][s] = 0;
   dijPQ pq;
   pq.emplace(0, s);
   
   while(pq.size()) {
      auto [d, u] = pq.top(); pq.pop();
      if(d > res[s][u]) continue;
      for(int v = 0; v < n; v++) {
         if(v != u && res[s][v] > d + adj[u][v]) {
            res[s][v] = d + adj[u][v];
            pq.emplace(res[s][v], v);
         }
      }
   }
}

auto threadEx = [&](int tnum) -> void {
   for(int i = tnum; i < n; i += num_threads) dijkstra(i);
};

vector<thread*> threads;
for(int i = 0; i < NUM_THREADS; i++)
   threads.push_back(new thread(threadEx, i));
for(auto th : threads) th->join();