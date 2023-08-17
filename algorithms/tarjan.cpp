/*
  0 <= ret[i] < # of distinct elements in ret
  ret[i] == ret[j] <=> i and j in same SCC
  ret[i] < ret[j] <=> i's SCC occurs before j's in toposort
*/
vector<int> tarjan(vector<vector<int>>& adj) {
  int n = (int)adj.size(), t = 0, ct = n - 1;
  vector<char> vis(n);
  vector<int> in(n), ret(n), stk;
  function<void(int)> dfs = [&](int cur) {
    in[cur] = ret[cur] = t++;
    vis[cur]++;
    stk.push_back(cur);
    for(int v : adj[cur]) {
      if(!vis[v]) dfs(v);
      if(vis[v] == 1) ret[cur] = min(ret[cur], ret[v]);
    }
    if(in[cur] == ret[cur]) {
      while(1) {
        int v = stk.back();
        stk.pop_back(); 
        ret[v] = ct; 
        vis[v]++;
        if(v == cur) break;
      }
      ct--;
    }
  };
  FOR(i,n) if(!vis[i]) dfs(i); 
  int m = *min_element(ret.begin(), ret.end());
  for(int& v : ret) v -= m;
  return ret;
}
