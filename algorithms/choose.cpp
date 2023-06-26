#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
using ll = long long;
using ii = pair<int,int>;

// b
const int MX = 3e6 + 10;
const ll MOD = 1e9 + 7;

ll fact[MX], factinv[MX];

ll mod_exp(ll x, ll y, ll mod) {
    ll res = 1;
    while(y > 0) {
        if(y & 1) res = res*x % mod;
        y >>= 1;
        x = x*x % mod;
    }
    return res;
}

void pre() {
  fact[0] = 1;
  factinv[0] = 1;
  FOR(i,MX-1) {
    fact[i + 1] = (fact[i] * (i + 1)) % MOD;
    factinv[i + 1] = mod_exp(fact[i + 1], MOD - 2, MOD);
  }
}

ll choose(int n, int k) {
  if(k > n) return 0;
  if(fact[0] == 0) pre();
  ll ret = (fact[n] * factinv[n - k]) % MOD;
  return (ret * factinv[k]) % MOD;
}
// e

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  cout << choose(9, 3) << '\n';
}
