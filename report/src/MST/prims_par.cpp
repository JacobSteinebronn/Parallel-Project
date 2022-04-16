void primMST(int** graph)
{
	int* parent = (int*)(calloc(num_nodes, sizeof(int)));
	// Key values used to pick minimum weight edge in cut
	int* key = (int*)(calloc(num_nodes, sizeof(int)));
	bool* mstSet = (bool*)(calloc(num_nodes, sizeof(bool)));;
	for (int i = 0; i < num_nodes; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	key[0] = 0;
	parent[0] = -1; 
	for (int count = 0; count < num_nodes - 1; count++)
	{
		int u = minKey(key, mstSet);
		// Add the picked vertex to the MST Set
		mstSet[u] = true;
		// Set parallelization point 
#pragma omp parallel for schedule(static)
		for (int v = 0; v < num_nodes; v++)
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}
}