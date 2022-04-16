void primMST(int** graph)
{
	for (int i = 0; i < num_nodes; i++)
		key[i] = INT_MAX, mstSet[i] = false;
	key[0] = 0;
	parent[0] = -1; 

	for (int c = 0; c < num_nodes - 1; c++)
	{
		int u = minKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		for (int v = 0; v < num_nodes; v++)
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}
}