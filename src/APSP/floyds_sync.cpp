int k = 0, numFinished = 0;
mutex finished_lock;

// Create mutexes, and lock them all to start.
vector<mutex*> waits;
for(int i = 0; i < NUM_THREADS; i++)
   waits.push_back(new mutex());
for(auto wait : waits)
   wait->lock();

auto threadEx = [&](int tnum) -> void {
   while(k < n) {
       // Complete the "I loop"s for this value of k
      for(int i = tnum; i < n; i += num_threads) {
         for(int j = 0; j < n; j++)
            if(adj[i][k] + adj[k][j] < adj[i][j]) 
               adj[i][j] = adj[i][k] + adj[k][j];
      }

      // We only allow one thread to "finish" at the same time, enforced with finished_lock.
      finished_lock.lock();
      if(numFinished == NUM_THREADS - 1) {
          // This thread is the last one to finish, so it's responsible for setting up all the global variables for the next iteration
          
          // increment k and reset numFinished
         ++k, numFinished = 0;
         // unlock every thread's mutex
         for(auto wait : waits)
            wait->unlock();
         waits[tnum]->lock();
         finished_lock.unlock();
      } else {
         numFinished++;
         finished_lock.unlock();
         waits[tnum]->lock();
      }
   }
};

vector<thread*> threads;
for(int i = 0; i < NUM_THREADS; i++) 
   threads.push_back(new thread(threadEx, i));
for(auto cur : threads) cur->join();