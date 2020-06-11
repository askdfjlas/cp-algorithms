#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define mp make_pair
#define PI 3.14159265358979323846264338327950288
typedef long long ll;
typedef pair<int,int> ii;

#define MAXN 100069
#define MOD1 1000002193
#define MOD2 1000011769
#define PVEC 1000003
#define PSTR 31

int VECPOW1[MAXN];
int VECPOW2[MAXN];
int STRPOW1[MAXN];
int STRPOW2[MAXN];

class rollingHash {
public:
  bool vec = false;
  int sz;
  ii val = mp(0, 0);
  ii* prefix;

  rollingHash(vector<int>& arr) {
    vec = true;
    sz = arr.size();
    prefix = new ii[sz + 1];
    prefix[0] = mp(0, 0);

    FOR(i,sz) {
      val.first = (val.first + 1ll * (arr[i] + 1) * VECPOW1[i]) % MOD1;
      val.second = (val.second + 1ll * (arr[i] + 1) * VECPOW2[i]) % MOD2;
      prefix[i + 1] = val;
    }
  }
};

ii hash(vector<int>& arr) {
  ii val = mp(0, 0);
  FOR(i,arr.size()) {
    val.first = (val.first + 1ll * (arr[i] + 1) * VECPOW1[i]) % MOD1;
    val.second = (val.second + 1ll * (arr[i] + 1) * VECPOW2[i]) % MOD2;
  }
  return val;
}

bool hash_eq(rollingHash& rh1, rollingHash& rh2, int l1, int r1, int l2, int r2) {
  if(r1 - l1 != r2 - l2)
    return false;

  ll hash11 = (rh1.prefix[r1 + 1].first - rh1.prefix[l1].first + MOD1) % MOD1;
  ll hash12 = (rh1.prefix[r1 + 1].second - rh1.prefix[l1].second + MOD2) % MOD2;
  ll hash21 = (rh2.prefix[r2 + 1].first - rh2.prefix[l2].first + MOD1) % MOD1;
  ll hash22 = (rh2.prefix[r2 + 1].second - rh2.prefix[l2].second + MOD2) % MOD2;

  int* pow1 = rh1.vec ? VECPOW1 : STRPOW1;
  int* pow2 = rh1.vec ? VECPOW2 : STRPOW2;

  if(l1 < l2) {
    hash11 = (hash11 * pow1[l2 - l1]) % MOD1;
    hash12 = (hash12 * pow2[l2 - l1]) % MOD2;
  }
  else {
    hash21 = (hash21 * pow1[l1 - l2]) % MOD1;
    hash22 = (hash22 * pow2[l1 - l2]) % MOD2;
  }

  return (hash11 == hash21 && hash12 == hash22);
}

void pre() {
  VECPOW1[0] = 1;
  VECPOW2[0] = 1;
  STRPOW1[0] = 1;
  STRPOW2[0] = 1;

  for(int i = 1; i < MAXN; i++) {
    VECPOW1[i] = (1ll * PVEC * VECPOW1[i - 1]) % MOD1;
    VECPOW2[i] = (1ll * PVEC * VECPOW2[i - 1]) % MOD2;
    STRPOW1[i] = (1ll * PSTR * STRPOW1[i - 1]) % MOD1;
    STRPOW2[i] = (1ll * PSTR * STRPOW2[i - 1]) % MOD2;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  pre();

  vector<int> vec1 = {0, 10, 20, 30, 50, 69, 100, 182821, 19191};
  vector<int> vec2 = {10, 20, 50, 69, 100, 182821, 19191, 1234, 12345, 123456, 0, 0};

  rollingHash rh1 = rollingHash(vec1);
  rollingHash rh2 = rollingHash(vec2);

  cout << hash_eq(rh1, rh2, 0, 0, 0, 0) << '\n'; // False - {0} != {10}
  cout << hash_eq(rh1, rh2, 1, 2, 0, 1) << '\n'; // True - {10, 20} = {10, 20}
  cout << hash_eq(rh1, rh2, 1, 4, 0, 3) << '\n'; // False
  cout << hash_eq(rh1, rh2, 7, 8, 5, 6) << '\n'; // True
}

// UPDATE N WHEN UR DONE AAAAAAAAAAAAAAAAAAAAAAAAAAA (if it applies lol)
