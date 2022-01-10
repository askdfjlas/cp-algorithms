#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Range sum segment tree
class segmentTree {
public:
  ll* tree;
  ll* lazyTree;
  int N;
  int size;

  void printTree() {
    for(int i = 0; i < size; i++) {
      cout << tree[i] << ' ';
    }
    cout << '\n';
  }

  void update(int qleft, int qright, ll delta) {
    update(qleft, qright, delta, 0, N - 1, 0);
  }

  void update(int qleft, int qright, ll delta, int left, int right, int index) {
    // If changes at this node haven't been updated
    if(lazyTree[index] != 0) {
      ll change = lazyTree[index];
      tree[index] += (right - left + 1)*lazyTree[index];
      lazyTree[index] = 0;

      // If not at a leaf, propagate to children
      if(left != right) {
	lazyTree[2*index + 1] += change;
	lazyTree[2*index + 2] += change;
      }
    }
    
    // Complete overlap
    if(left >= qleft && right <= qright) {
      tree[index] += (right - left + 1)*delta;

      // If not a leaf
      if(left != right) {
	lazyTree[2*index + 1] += delta;
	lazyTree[2*index + 2] += delta;  
      }
    }

    // Partial overlap
    else if(!(right < qleft || left > qright)) {
      int mid = (left + right)/2;
      update(qleft, qright, delta, left, mid, 2*index + 1);
      update(qleft, qright, delta, mid + 1, right, 2*index + 2);

      tree[index] = tree[2*index + 1] + tree[2*index + 2];
    }
  }

  ll query(int qleft, int qright) {
    return query(qleft, qright, 0, N - 1, 0);
  }

  ll query(int qleft, int qright, int left, int right, int index) {
    // If changes at this node haven't been updated
    if(lazyTree[index] != 0) {
      ll change = lazyTree[index];
      tree[index] += (right - left + 1)*change;
      lazyTree[index] = 0;

      // If not at a leaf, propagate to children
      if(left != right) {
	lazyTree[2*index + 1] += change;
	lazyTree[2*index + 2] += change;
      }
    }
    
    // Complete overlap
    if(left >= qleft && right <= qright) {
      return tree[index];
    }
    // No overlap
    if(right < qleft || left > qright) {
      return 0;
    }
    // Partial
    int mid = (left + right)/2;
    return query(qleft, qright, left, mid, 2*index + 1) +
	   query(qleft, qright, mid + 1, right, 2*index + 2);
  }

  void createTree(vector<ll>& arr, int left, int right, int index) {
    // Leaf
    if(left == right) {
      tree[index] = arr[left];
    }
    // Non-leaf
    else {
      int mid = (left + right)/2;
      createTree(arr, left, mid, 2*index + 1);
      createTree(arr, mid + 1, right, 2*index + 2);
      tree[index] = tree[2*index + 1] + tree[2*index + 2];
    }
  }
  
  segmentTree(vector<ll>& arr) {
    N = arr.size();

    // Find next highest 2^x - 1
    int start = 2;
    while((start - 1) < 2*N) start *= 2;
    size = start - 1;

    // Create space, initialize to 0 for range sum query
    tree = new ll[size];
    for(int i = 0; i < size; i++) {
      tree[i] = 0;
    }
    // Same for lazy tree, init to 0
    lazyTree = new ll[size];
    memset(lazyTree, 0, size*sizeof(ll));

    // Create tree
    createTree(arr, 0, N - 1, 0);
  }
};

int main() {
  // Testing
  vector<ll> test = {-23, 88, 15, 99, 100, -1000, 2323, -3, 0, 895};

  segmentTree tree = segmentTree(test);
  tree.printTree();
  tree.update(0, 4, -2);
  cout << tree.query(6, 7) << ' ' << tree.query(0, 3) << '\n';
  tree.update(0, 9, 105);
  cout << tree.query(8, 9) << ' ' << tree.query(0, 9) << ' ' << tree.query(0, 4) << '\n';
  return 0;
}
 
