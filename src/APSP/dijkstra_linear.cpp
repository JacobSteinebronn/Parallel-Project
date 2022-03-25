void dijkstra(int s) {
   for(int i = 0; i < n; i++) res[s][i] = oo;
   res[s][s] = 0;
   
   for(int i = 0; i < n; i++){
      // Find lowest distance not-done node
      int u = -1;
      for(int v = 0; v < n; v++)
         if(!done[s][v])
            if(u == -1 || res[s][v] < res[s][u])
               u = v;
      done[s][u] = 1;
      // explore u's edges
      for(int v = 0; v < n; v++)
         if(res[s][v] > res[s][u] + adj[u][v]) 
            res[s][v] = res[s][u] + adj[u][v];
   }
}

auto threadEx = [&](int tnum) -> void {
   for(int i = tnum; i < n; i += num_threads) dijkstra(i);
};

vector<thread*> threads;
for(int i = 0; i < NUM_THREADS; i++)
   threads.push_back(new thread(threadEx, i));
for(auto th : threads) th->join();