void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if(x != y) {
    if(ranks[x] < ranks[y]) {
      parents[x] = y;
    } else if(ranks[x] > ranks[y]) {
      parents[y] = x;
    } else {
      parents[x] = y;
      ranks[y]++;
    }
  }
}