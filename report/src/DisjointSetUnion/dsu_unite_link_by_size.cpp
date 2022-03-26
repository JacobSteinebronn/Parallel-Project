void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if(x != y) {
    if(sizes[x] < sizes[y]) {
      parents[x] = y;
      sizes[y] += sizes[x];
    } else {
      parents[y] = x;
      sizes[x] += sizes[y];
    }
  }
}