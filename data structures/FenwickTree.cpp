#include <bits/stdc++.h>
using namespace std;

template <typename T> struct FenwickTree {
  int size = 1, high_bit = 1;
  vector<T> tree;
  FenwickTree(int _size) : size(_size) {
    tree.resize(size + 1);
    while((high_bit << 1) <= size) high_bit <<= 1;
  }
  FenwickTree(vector<T>& arr) : FenwickTree(arr.size()) {
    for(int i = 0; i < size; i++) update(i, arr[i]); 
  }
  int lower_bound(T x) {
    int res = 0; T cur = 0;
    for(int bit = high_bit; bit > 0; bit >>= 1) {
      if((res|bit) <= size && cur + tree[res|bit] < x) {
        res |= bit; cur += tree[res];
      }
    }
    return res;
  }
  T prefix_sum(int i) {
    T ret = 0;
    for(i++; i > 0; i -= (i & -i)) ret += tree[i];
    return ret;
  }
  T range_sum(int l, int r) { return (l > r) ? 0 : prefix_sum(r) - prefix_sum(l - 1); }
  void update(int i, T delta) { for(i++; i <= size; i += (i & -i)) tree[i] += delta; }
};

int main() {
  // Testing
  vector<int> test = {-23, 88, 15, 99, 100, -1000, 2323, -3, 0, 895};

  FenwickTree<int> tree = FenwickTree<int>(test);
  
  cout << tree.lbound(-23) << ' ' << tree.lbound(-22) << '\n';
  cout << tree.prefixSum(0) << ' ' << tree.prefixSum(5) << ' ' << tree.prefixSum(8) << '\n';
  tree.update(0, 100);
  cout << tree.prefixSum(5) << ' ' << tree.prefixSum(8) << '\n';
  tree.update(8, -5235);
  cout << tree.prefixSum(5) << ' ' << tree.prefixSum(8) << '\n';
}
