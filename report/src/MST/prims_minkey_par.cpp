int minKey(int key[], bool mstSet[])
{
	 int min = INT_MAX, index, i;
     // set the outer nest to be parallel so that intialized data is hosted on the correct thread
#pragma omp parallel
    {
        int index_local = index;
        int min_local = min;
        // Run this for-loop concurrently with a nowait condition
#pragma omp for nowait
        for (i = 0; i < num_nodes; i++)
        {
            if (mstSet[i] == false && key[i] < min_local)
            {
                min_local = key[i];
                index_local = i;
            }
        }
        // Check if the local min is less than the shared min
#pragma omp critical
        {
            if (min_local < min)
            {
                min = min_local;
                index = index_local;
            }
        }
    }
    return index;
}