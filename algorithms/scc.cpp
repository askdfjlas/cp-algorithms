/*
  0 <= ret[i] < n
  ret[i] == ret[j] <=> i and j in same SCC
  ret[i] < ret[j] <=> i's SCC occurs before j's in toposort
*/
vector<int> scc(int n, vector<ii>& edges) {
  vector<int> g[n], ginv[n];
  vector<int> out, ret(n);
  for(auto [u, v] : edges) {
    g[u].push_back(v);
    ginv[v].push_back(u);
  }
  function<void(int)> dfs = [&](int cur) {
    ret[cur] = -1;
    for(int v : g[cur]) {
      if(ret[v]) continue;
      dfs(v);
    }
    out.push_back(cur);
  };
  function<void(int,int)> dfs2 = [&](int cur, int t) {
    ret[cur] = t;
    for(int v : ginv[cur]) {
      if(ret[v] != -1) continue;
      dfs2(v, t);
    }
  };
  FOR(i,n) if(!ret[i]) dfs(i);
  int t = 0;
  for(int i = n - 1; i >= 0; i--) {
    if(ret[out[i]] != -1) continue;
    dfs2(out[i], t);
    t++;
  }
  return ret;
}
