for(int k = 0; k < n; k++)
   for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
         // edge relaxation of i->k->j into i->j
         if(adj[i][k] + adj[k][j] < adj[i][j])
            adj[i][j] = adj[i][k] + adj[k][j];