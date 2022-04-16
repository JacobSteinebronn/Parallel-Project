#pragma omp parallel for schedule(static)
    for (int v = 0; v < num_nodes; v++)
        // Update the key only if graph[u][v] is smaller than key[v]
        if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
            parent[v] = u, key[v] = graph[u][v];