#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define mp make_pair
#define PI 3.14159265358979323846264338327950288
typedef long long ll;
typedef pair<int,int> ii;

// REMEMBER TO WRITE pre()
const ll MOD = 998244353;
const int GEN = 3;
const int MX = (1 << 20);  // 1048576
ll roots[MX], invroots[MX];
int nttmem[MX];

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
  ll w = mod_exp(GEN, (MOD - 1)/MX, MOD);
  ll winv = mod_exp(w, MOD - 2, MOD);
  ll top = 1, bottom = 1;
  FOR(i,MX) {
    roots[i] = top;
    invroots[i] = bottom;
    top = (top * w) % MOD;
    bottom = (bottom * winv) % MOD;
  }
}

void ntt(int* coeffs, ll* w, int start, int bounce, int l, int mult) {
  int len = MX/(bounce * mult);
  if(len > 2) {
    ntt(coeffs, w, start, bounce << 1, l, mult);
    ntt(coeffs, w, start + bounce, bounce << 1, l + len/2, mult);
  }
  else {
    nttmem[l] = coeffs[start];
    nttmem[l + len/2] = coeffs[start + bounce];
  }
  
  FOR(i,len/2) {
    int rootidx = i * bounce;
    int t = (nttmem[i + l] + w[mult * rootidx] * nttmem[i + l + len/2]) % MOD;
    nttmem[i + l + len/2] = (nttmem[i + l] + (MOD - w[mult * rootidx]) * nttmem[i + l + len/2]) % MOD;
    nttmem[i + l] = t;
  }
}

void ntt(int* coeffs, int* mem, int len, bool fwd) {
  ll* w = fwd ? roots : invroots;
  ntt(coeffs, w, 0, 1, 0, MX/len);
  
  int mxinv = mod_exp(len, MOD - 2, MOD);
  FOR(i,len) {
    mem[i] = fwd ? nttmem[i] : (1ll * nttmem[i] * mxinv) % MOD; 
  }
}

// Result in a, overwrites both
void convolve(int* a, int* b, int len) {
  ntt(a, a, len, true);
  ntt(b, b, len, true);
  
  FOR(i,len) {
    a[i] = (1ll * a[i] * b[i]) % MOD;
  }
  
  ntt(a, a, len, false);
}

int p1[MX], p2[MX];

// https://judge.yosupo.jp/problem/convolution_mod
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  pre();
  int n, m;
  cin >> n >> m;
  
  FOR(i,n) cin >> p1[i];
  FOR(i,m) cin >> p2[i];
  
  convolve(p1, p2, MX);
  FOR(i,n+m-1) {
    cout << p1[i] << ' ';
  }
  cout << '\n';
}

// UPDATE N WHEN UR DONE AAAAAAAAAAAAAAAAAAAAAAAAAAA (if it applies lol)