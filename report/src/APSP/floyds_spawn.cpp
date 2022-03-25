auto threadEx = [&](int tnum, int k) -> void {
   for(int i = tnum; i < n; i += NUM_THREADS) {
      for(int j = 0; j < n; j++)
         if(adj[i][k] + adj[k][j] < adj[i][j]) 
            adj[i][j] = adj[i][k] + adj[k][j];
   }
};

for(int k = 0; k < n; k++){
   vector<thread*> threads;
   for(int i = 0; i < NUM_THREADS; i++) 
      threads.push_back(new thread(threadEx, i, k));
   for(auto cur : threads) cur->join();
}