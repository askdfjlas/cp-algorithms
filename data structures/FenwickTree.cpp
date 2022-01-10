#include <bits/stdc++.h>
using namespace std;

template <class T>
struct FenwickTree {
  T* tree;
  T mxbit = 1;
  int size;
  
  T prefixSum(int i) {
    i++;
    T ret = 0;
    while(i > 0) {
      ret += tree[i];
      i -= (i & -i);
    }
    return ret;
  }
  
  T rangeSum(int l, int r) {
    return prefixSum(r) - prefixSum(l - 1);
  }
  
  int lbound(T x) {
    int res = 0;
    T curr = 0;
    T bit = mxbit;
    while(bit) {
      if((res|bit) <= size && curr + tree[res|bit] < x) {
        res |= bit;
        curr += tree[res];
      }
      bit >>= 1;
    }
    return res;
  }
  
  void update(int i, T delta) {
    i++;
    while(i <= size) {
      tree[i] += delta;
      i += (i & -i); 
    }
  }
  
  FenwickTree(int sz) {
    size = sz;
    tree = new T[size+1];
    memset(tree, 0, (size+1)*sizeof(T));
    while((mxbit << 1) <= size) mxbit <<= 1;
  }
  
  FenwickTree(vector<T>& arr) : FenwickTree(arr.size()) {
    for(int i = 0; i < size; i++)
      update(i, arr[i]); 
  }
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
