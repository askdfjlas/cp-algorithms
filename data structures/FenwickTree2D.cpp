#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define FORR(x,a,b) for(int x=a;x<=b;x++)
using ll = long long;
using ii = pair<int,int>;

template <typename T> struct FenwickTree2D {
  int height, width;
  vector<vector<T>> tree;
  FenwickTree2D() = default;
  FenwickTree2D(int height, int width) : height(height), width(width) {
    tree.resize(height + 1);
    FOR(i,height+1) tree[i].resize(width + 1);
  }
  FenwickTree2D(const vector<vector<T>>& mat) : FenwickTree2D(mat.size(), mat.size() ? mat[0].size() : 0) {
    FOR(i,height) FOR(j,width) update(i, j, mat[i][j]); 
  }
  T prefix_sum(int i, int j) {
    T ret = 0;
    for(i++; i > 0; i -= (i & -i)) for(int k = j + 1; k > 0; k -= (k & -k))
      ret += tree[i][k];
    return ret;
  }
  T range_sum(int d, int l, int u, int r) {
    if(l > r || d > u) return 0;
    return prefix_sum(u, r) - prefix_sum(d - 1, r) - prefix_sum(u, l - 1) + prefix_sum(d - 1, l - 1);
  }
  void update(int i, int j, T delta) {
    for(i++; i <= height; i += (i & -i)) for(int k = j + 1; k <= width; k += (k & -k))
      tree[i][k] += delta;
  }
  void set(int i, int j, T x) { update(i, j, x - range_sum(i, j, i, j)); }
};

// https://leetcode.com/problems/range-sum-query-2d-immutable/