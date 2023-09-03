#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define FORR(x,a,b) for(int x=a;x<=b;x++)
using ll = long long;
using ii = pair<int,int>;

struct LCA {
  int n, log = 1, _t = 0;
  vector<vector<int>> adj, st;
  vector<int> id, dep;
  LCA() = default;
  LCA(const vector<int>& p) : n((int)p.size()) {
    while((1 << log) < (n << 1)) log++;
    adj.resize(n);
    st.resize(log);
    id.resize(n);
    dep.resize(n);
    FORR(i,1,n-1) adj[p[i]].push_back(i);
    FOR(i,log) st[i].resize(2*n - 1);
    dfs(0, 0);
    FORR(i,1,log-1) FOR(j,2*n-1) {
      int c1 = st[i - 1][min(j + (1 << (i - 1)), 2*n - 2)], c2 = st[i - 1][j];
      st[i][j] = dep[c1] < dep[c2] ? c1 : c2;
    }
  }
  void dfs(int cur, int d) {
    st[0][_t] = cur;
    id[cur] = _t;
    dep[cur] = d;
    _t++;
    for(int v : adj[cur] ){
      dfs(v, d + 1);
      st[0][_t] = cur;
      _t++;
    }
  }
  int lca(int u, int v) {
    int l = id[u], r = id[v];
    if(l > r) swap(l, r);
    int i = 31 - __builtin_clz(r - l + 1); 
    int c1 = st[i][l], c2 = st[i][r - (1 << i) + 1];
    return dep[c1] < dep[c2] ? c1 : c2;
  }
};

struct KthAncestor {
  int n, log = 1;
  vector<vector<int>> par;
  KthAncestor() = default;
  KthAncestor(const vector<int>& p) : n((int)p.size()) {
    while((1 << log) <= n) log++;
    par.resize(log);
    FOR(i,log) par[i].resize(n);
    par[0] = p;
    FORR(i,1,log-1) FOR(j,n)
      par[i][j] = par[i - 1][j] == -1 ? -1 : par[i - 1][par[i - 1][j]];
  }
  int query(int u, int k) {
    int ret = u;
    while(k && ret != -1) {
      int lo = (k & -k);
      ret = par[31 - __builtin_clz(lo)][ret];
      k -= lo;
    } 
    return ret;
  }
};

// https://judge.yosupo.jp/problem/lca (try again someday when judge is back up)
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  int n, q;
  cin >> n >> q;
  vector<int> p(n);
  FOR(i,n-1) cin >> p[i + 1];
  LCA o(p);
  FOR(i,q) {
    int u, v;
    cin >> u >> v;
    cout << o.lca(u, v) << '\n';
  }
}
