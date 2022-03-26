int find(int x) {
  while(x != parents[x]) {
    int y = parents[x];
    int z = parents[y];
    parents[x] = z;
    x = y;
  }
  return x;
}