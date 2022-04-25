int find(int x) {
  if(x == parents[x]) {
    return x;
  }
  parents[x] = find(parents[x]);
  return parents[x];
}