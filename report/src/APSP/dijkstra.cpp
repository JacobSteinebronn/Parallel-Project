typedef pair<ll, int> st;
typedef priority_queue<st, vector<st>, greater<st>> dijPQ;

// Fills in every column of res[s]; that is, 
// shortest distance from s to every node.
void dijkstra(int s) {
   for(int i = 0; i < n; i++) res[s][i] = oo;
   res[s][s] = 0;
   dijPQ pq;
   pq.emplace(0, s);
   
   while(pq.size()) {
      auto [d, u] = pq.top(); pq.pop();
      if(d > res[s][u]) continue;
      for(int v = 0; v < n; v++) {
         if(v != u && res[s][v] > d + adj[u][v]) {
            res[s][v] = d + adj[u][v];
            pq.emplace(res[s][v], v);
         }
      }
   }
}

for(int s = 0; s < n; s++) 
   dijkstra(s);