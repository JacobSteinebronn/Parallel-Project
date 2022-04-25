vector<thread*> threads(numThreads);

for(int threadIdx = 0; threadIdx < numThreads; ++threadIdx){
    int startEdge = numHandledByEachThread * threadIdx;
    int endEdge = numHandledByEachThread * (threadIdx + 1);

    endEdge = min(endEdge, numEdges);

    threads[threadIdx] = new thread(updateEdges, startEdge, endEdge);
}

for(int threadIdx = 0; threadIdx < numThreads; ++threadIdx){
    threads[threadIdx]->join();
}