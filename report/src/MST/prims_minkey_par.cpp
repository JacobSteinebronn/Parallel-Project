int minKey(int key[], bool mstSet[])
{
	 int min = INT_MAX, index, i;
#pragma omp parallel
    {
        int index_local = index, min_local = min;
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