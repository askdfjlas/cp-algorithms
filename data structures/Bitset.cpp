#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define FORR(x,a,b) for(int x=a;x<=b;x++)
using ll = long long;
using ii = pair<int,int>;

struct Bitset {
  using ull = unsigned long long;
  static const int BLOCKSZ = CHAR_BIT * sizeof(ull);
  int n;
  vector<ull> a;
  Bitset(int n) : n(n) { a.resize((n + BLOCKSZ - 1)/BLOCKSZ); }
  void set(int p, bool v) {
    ull b = (1ull << (p - BLOCKSZ * (p/BLOCKSZ)));
    v ? a[p/BLOCKSZ] |= b : a[p/BLOCKSZ] &= ~b;
  }
  void flip(int p) {
    ull b = (1ull << (p - BLOCKSZ * (p/BLOCKSZ)));
    a[p/BLOCKSZ] ^= b;
  }
  string to_string() {
    string res;
    FOR(i,n) res += operator[](i) ? '1' : '0';
    return res;
  }
  int count() {
    int sz = (int)a.size(), ret = 0;
    FOR(i,sz) ret += __builtin_popcountll(a[i]); 
    return ret;
  }
  int size() { return n; }
  bool operator[](int p) { return a[p/BLOCKSZ] & (1ull << (p - BLOCKSZ * (p/BLOCKSZ))); }
  bool operator==(const Bitset& other) {
    if(n != other.n) return false;
    FOR(i,(int)a.size()) if(a[i] != other.a[i]) return false;
    return true;
  }
  bool operator!=(const Bitset& other) { return !operator==(other); }
  Bitset& operator<<=(int x) {
    int sz = (int)a.size(), sh = x/BLOCKSZ, xtra = x - sh * BLOCKSZ, rem = BLOCKSZ - xtra;
    if(!xtra) FOR(i,sz-sh) a[i] = a[i + sh] >> xtra; 
    else {
      FOR(i,sz-sh-1) a[i] = (a[i + sh] >> xtra) | (a[i + sh + 1] << rem); 
      if(sz - sh - 1 >= 0) a[sz - sh - 1] = a[sz - 1] >> xtra;
    }
    FORR(i,max(0,sz-sh),sz-1) a[i] = 0;
    return *this;
  }
  Bitset& operator>>=(int x) {
    int sz = (int)a.size(), sh = x/BLOCKSZ, xtra = x - sh * BLOCKSZ, rem = BLOCKSZ - xtra;
    if(!xtra) for(int i = sz - 1; i >= sh; i--) a[i] = a[i - sh] << xtra;
    else {
      for(int i = sz - 1; i > sh; i--) a[i] = (a[i - sh] << xtra) | (a[i - sh - 1] >> rem);
      if(sh < sz) a[sh] = a[0] << xtra;
    }
    for(int i = min(sz-1,sh-1); i >= 0; i--) a[i] = 0;
    a[sz - 1] <<= (sz * BLOCKSZ - n);
    a[sz - 1] >>= (sz * BLOCKSZ - n);
    return *this;
  }
  Bitset& operator&=(const Bitset& other) { FOR(i,(int)a.size()) a[i] &= other.a[i]; return *this; }
  Bitset& operator|=(const Bitset& other) { FOR(i,(int)a.size()) a[i] |= other.a[i]; return *this; }
  Bitset& operator^=(const Bitset& other) { FOR(i,(int)a.size()) a[i] ^= other.a[i]; return *this; }
  Bitset operator~() {
    int sz = (int)a.size();
    Bitset ret(*this);
    FOR(i,sz) ret.a[i] = ~ret.a[i];
    ret.a[sz - 1] <<= (sz * BLOCKSZ - n);
    ret.a[sz - 1] >>= (sz * BLOCKSZ - n);
    return ret;
  }
  Bitset operator&(const Bitset& other) { return (Bitset(*this) &= other); }
  Bitset operator|(const Bitset& other) { return (Bitset(*this) |= other); }
  Bitset operator^(const Bitset& other) { return (Bitset(*this) ^= other); }
  Bitset operator<<(int x) { return (Bitset(*this) <<= x); }
  Bitset operator>>(int x) { return (Bitset(*this) >>= x); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  const int BSZ = 8293;
  bitset<BSZ> bs1, bs2;
  Bitset tbs1(BSZ), tbs2(BSZ);
  FOR(i,1000) {
    FOR(j,BSZ) {
      if(rng() % 3 == 0) {
        bs1.set(j, 1);
        tbs1.set(j, 1);
      }
      if(rng() % 3 == 0) {
        bs1.set(j, 0);
        tbs1.set(j, 0);
      }
      if(rng() % 3 == 0) {
        bs1.flip(j);
        tbs1.flip(j);
      }
      if(rng() % 3 == 0) {
        bs2.set(j, 1);
        tbs2.set(j, 1);
      }
      if(rng() % 3 == 0) {
        bs2.set(j, 0);
        tbs2.set(j, 0);
      }
      if(rng() % 3 == 0) {
        bs2.flip(j);
        tbs2.flip(j);
      }
    }
    int rs = (rng() % (2*BSZ)), ls = (rng() % (2*BSZ));
    bs1 <<= rs; tbs1 = (tbs1 >> rs);
    bs2 >>= ls; tbs2 = (tbs2 << ls);
    
    if(rng() % 3 == 0) {
      bs1 = bs1 | bs2;
      tbs1 = tbs1 | tbs2;
    }
    if(rng() % 3 == 0) {
      bs1 = bs1 & bs2;
      tbs1 = tbs2 & tbs1;
    }
    if(rng() % 3 == 0) {
      bs2 = bs2 ^ bs1;
      tbs2 = tbs1 ^ tbs2;
    }
    if(rng() % 3 == 0) {
      bs1 = ~bs1;
      tbs1 = ~tbs1;
    }
    if(rng() % 3 == 0) {
      bs2 = ~bs1;
      tbs2 = ~tbs1;
    }
    
    string s1 = bs1.to_string(), s2 = bs2.to_string();
    string t1 = tbs1.to_string(), t2 = tbs2.to_string();
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    assert(s1 == t1 && s2 == t2);
    
    auto cpy = Bitset(tbs1);
    assert(tbs1 == cpy);
    cpy.flip(rng() % BSZ);
    assert(tbs1 != cpy);
    
    assert((int)bs1.count() == tbs1.count());
    assert((int)bs2.count() == tbs2.count());
  }
}
