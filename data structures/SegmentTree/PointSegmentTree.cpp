#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
using ll = long long;
using ii = pair<int,int>;

template <class T> struct PointSegmentTree {
  int size = 1;
  vector<T> tree;
  PointSegmentTree(int n) : PointSegmentTree(vector<T>(n)) {}
  PointSegmentTree(const vector<T>& arr) {
    while(size < (int)arr.size())
      size <<= 1;
    tree = vector<T>(size << 1);
    for(int i = size + arr.size() - 1; i >= 1; i--)
      if(i >= size) tree[i] = arr[i - size];
      else _consume(i);
  }
  void set(int i, T val) {
    tree[i += size] = val;
    for(i >>= 1; i >= 1; i >>= 1)
      _consume(i); 
  }
  void update(int i, T val) { set(i, tree[i + size] * val); }
  T get(int i) { return tree[i + size]; }
  T query(int l, int r) {
    if(l == r + 1) return T();
    T resl, resr;
    for(l += size, r += size + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) resl = resl * tree[l++];
      if(r & 1) resr = tree[--r] * resr;
    }
    return resl * resr;
  }
  T query_all() { return tree[1]; }
  void _consume(int i) { tree[i] = tree[i << 1] * tree[i << 1 | 1]; }
};

struct SegType {
  ll a; 
  SegType() : SegType(0) {}
  SegType(ll _a) : a(_a) {}
  SegType operator*(SegType t) {
    return SegType(a + t.a);
  }
};

// https://judge.yosupo.jp/problem/point_add_range_sum
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  int n, q;
  cin >> n >> q;
  vector<SegType> arr(n);
  FOR(i,n) cin >> arr[i].a;

  PointSegmentTree<SegType> tree(arr);
  while(q--) {
    int t, a, b;
    cin >> t >> a >> b;
    if(t == 0) tree.update(a, b);
    else cout << tree.query(a, b - 1).a << '\n';
  }
}
