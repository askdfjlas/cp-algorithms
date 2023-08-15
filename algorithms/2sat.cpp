#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
typedef long long ll;
typedef pair<int,int> ii;

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

// 0 => impossible, 1 => possible
pair<int,vector<int>> sat2(int n, vector<pair<int,int>>& clauses) {
  vector<int> ans(n);
  vector<ii> edges;
  for(auto [x, y] : clauses) {
    x = x < 0 ? -x + n : x;
    y = y < 0 ? -y + n : y;
    int nx = x <= n ? x + n : x - n;
    int ny = y <= n ? y + n : y - n;
    edges.push_back({nx, y});
    edges.push_back({ny, x});
  }
  vector<int> idx = scc(2*n + 1, edges);
  for(int i = 1; i <= n; i++) {
    if(idx[i] == idx[i + n]) return {0, {}};
    ans[i - 1] = idx[i + n] < idx[i];
  }
  return {1, ans};
}

// https://judge.yosupo.jp/problem/two_sat
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  char buf[100];
  int n, m;
  scanf("%s %s %d %d", buf, buf, &n, &m);
  
  vector<pair<int,int>> clauses(m);
  FOR(i,m) scanf("%d %d %s", &clauses[i].first, &clauses[i].second, buf);
  auto [sol, x] = sat2(n, clauses);
  if(!sol) {
    printf("s UNSATISFIABLE\n");
    exit(0);
  }
  
  printf("s SATISFIABLE\nv ");
  for(int i = 1; i <= n; i++) {
    if(x[i - 1]) printf("%d ", i);
    else printf("%d ", -i);
  }
  printf("0\n");
}
