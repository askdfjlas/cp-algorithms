#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define PI 3.14159265358979323846264338327950288
typedef long long ll;
typedef pair<int,int> ii;

void enumerate_triangles(vector<pair<int,int>>& edges, function<void(int,int,int)> f) {
  int n = 0;
  for(auto [u, v] : edges) n = max({n, u + 1, v + 1});
  vector<int> deg(n);
  vector<int> g[n];
  for(auto [u, v] : edges) {
    deg[u]++;
    deg[v]++;
  }
  for(auto [u, v] : edges) {
    if(u == v) continue;
    if(deg[u] > deg[v] || (deg[u] == deg[v] && u > v))
      swap(u, v);
    g[u].push_back(v);
  }
  vector<int> flag(n);
  for(int i = 0; i < n; i++) {
    for(int v : g[i]) flag[v] = 1;
    for(int v : g[i]) for(int u : g[v]) {
      if(flag[u]) f(i, v, u);
    }
    for(int v : g[i]) flag[v] = 0;
  }
}

const ll MOD = 998244353;

// https://judge.yosupo.jp/problem/enumerate_triangles
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  int n, m;
  cin >> n >> m;
  
  ll x[n];
  vector<pair<int,int>> edges(m);
  FOR(i,n) cin >> x[i];
  FOR(i,m) cin >> edges[i].first >> edges[i].second;
  
  ll ans = 0;
  enumerate_triangles(edges, [&](int i, int j, int k) {
    ll contr = (x[i] * x[j]) % MOD;
    ans = (ans + contr * x[k]) % MOD;
  });
  cout << ans << '\n';
}
