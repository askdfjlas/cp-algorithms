#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
typedef long long ll;
typedef pair<int,int> ii;

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

// 0 => impossible, 1 => possible
pair<int,vector<int>> sat2(int n, vector<pair<int,int>>& clauses) {
  vector<int> ans(n);
  vector<vector<int>> adj(2*n+1);
  for(auto [x, y] : clauses) {
    x = x < 0 ? -x + n : x;
    y = y < 0 ? -y + n : y;
    int nx = x <= n ? x + n : x - n;
    int ny = y <= n ? y + n : y - n;
    adj[nx].push_back(y);
    adj[ny].push_back(x);
  }
  vector<int> idx = tarjan(adj);
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
  
  string s;
  int n, m, ig;
  cin >> s >> s >> n >> m;
  vector<pair<int,int>> clauses(m);
  FOR(i,m) cin >> clauses[i].first >> clauses[i].second >> ig;
  auto [sol, x] = sat2(n, clauses);
  if(!sol) {
    cout << "s UNSATISFIABLE\n";
    exit(0);
  }
  cout << "s SATISFIABLE\nv ";
  for(int i = 1; i <= n; i++) {
    if(x[i - 1]) cout << i << ' ';
    else cout << -i << ' ';
  }
  cout << "0\n";
}
