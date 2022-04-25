int find(int x) {
  while(parents[x] != x) {
    x = parents[x];
  }
  return x;
}