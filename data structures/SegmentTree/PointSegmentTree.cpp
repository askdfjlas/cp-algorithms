#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
using ll = long long;
using ii = pair<int,int>;

template <class T> struct PointSegmentTree {
  int size = 1;
  vector<T> tree;
  PointSegmentTree(int n) : PointSegmentTree(vector<T>(n)) {}
  PointSegmentTree(vector<T>& arr) {
    while(size < (int)arr.size())
      size <<= 1;
    tree = vector<T>(size << 1);
    for(int i = size + arr.size() - 1; i >= 1; i--)
      if(i >= size) tree[i] = arr[i - size];
      else consume(i);
  }
  void set(int i, T val) {
    tree[i += size] = val;
    for(i >>= 1; i >= 1; i >>= 1)
      consume(i); 
  }
  T get(int i) { return tree[i + size]; }
  T query(int l, int r) {
    T resl, resr;
    for(l += size, r += size + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) resl = resl * tree[l++];
      if(r & 1) resr = tree[--r] * resr;
    }
    return resl * resr;
  }
  T query_all() { return tree[1]; }
  void consume(int i) { tree[i] = tree[i << 1] * tree[i << 1 | 1]; }
};


struct SegInfo {
  ll v; 
  SegInfo() : SegInfo(0) {}
  SegInfo(ll val) : v(val) {}
  SegInfo operator*(SegInfo b) {
    return SegInfo(v + b.v);
  }
};

// https://judge.yosupo.jp/problem/point_add_range_sum
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  int n, q;
  cin >> n >> q;
  vector<SegInfo> arr(n);
  FOR(i,n) cin >> arr[i].v;

  PointSegmentTree<SegInfo> tree(arr);
  while(q--) {
    int t, a, b;
    cin >> t >> a >> b;
    if(t == 0) tree.set(a, tree.get(a) * SegInfo(b));
    else cout << tree.query(a, b - 1).v << '\n';
  }
}
