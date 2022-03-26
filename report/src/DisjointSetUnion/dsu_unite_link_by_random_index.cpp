void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if(x != y) {
    if(index[x] < index[y]) {
      parents[x] = y;
    } else {
      parents[y] = x;
    }
  }
}