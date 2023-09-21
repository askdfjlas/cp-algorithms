struct BipartiteDsu {
  vector<int> par, col, sz;
  BipartiteDsu(int n) {
    par.resize(n);
    col.resize(n);
    sz.resize(n);
    FOR(i,n) {
      par[i] = i;
      sz[i] = 1;
    }
  }
  ii find(int u) {
    int t = u, o = u, xo = 0;
    while(par[t] != t) {
      xo ^= col[t];
      t = par[t];
    }
    while(par[u] != u) {
      int nxt = par[u], c = col[u];
      par[u] = t;
      col[u] = xo;
      xo ^= c;
      u = nxt;
    }
    return {t, col[o]};
  }
  int join(int u, int v) {
    auto [a, ca] = find(u);
    auto [b, cb] = find(v);
    if(a == b && ca == cb) return -2;
    if(a == b) return -1;
    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    par[b] = a;
    col[b] = (ca == cb);
    return a;
  }
};
