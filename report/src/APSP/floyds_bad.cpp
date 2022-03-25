auto threadEx = [&](int threadNum) -> void {
   for(int k = threadNum; k < n; k += NUM_THREADS)
      for(int i = 0; i < n; i++)
         for(int j = 0; j < n; j++)
            if(adj[i][k] + adj[k][j] < adj[i][j])
               adj[i][j] = adj[i][k] + adj[k][j];
};

vector<thread*> threads;
for(int i = 0; i < NUM_THREADS; i++)
   threads.push_back(new thread(threadEx, i));
