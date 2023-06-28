struct Dsu {
  vector<int> par, sz;
  Dsu(int n) {
    par.resize(n);
    sz.resize(n);
    FOR(i,n) {
      par[i] = i;
      sz[i] = 1;
    }
  }
  int find(int u) {
    int t = u;
    while(par[t] != t)
      t = par[t];
    while(par[u] != u) {
      int nxt = par[u];
      par[u] = t;
      u = nxt;
    }
    return t;
  }
  int join(int u, int v) {
    int a = find(u), b = find(v);
    if(a == b) return -1;
    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    par[b] = a;
    return a;
  }
};
