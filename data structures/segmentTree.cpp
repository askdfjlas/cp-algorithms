#include <bits/stdc++.h>
using namespace std;

// RMQ segment tree
class segmentTree {
public:
  int* tree;
  int* lazyTree;
  int N;
  int size;

  void printTree() {
    for(int i = 0; i < size; i++) {
      cout << tree[i] << ' ';
    }
    cout << '\n';
  }

  void update(int qleft, int qright, int delta) {
    update(qleft, qright, delta, 0, N - 1, 0);
  }

  void update(int qleft, int qright, int delta, int left, int right, int index) {
    // If changes at this node haven't been updated
    if(lazyTree[index] != 0) {
      int change = lazyTree[index];
      tree[index] += lazyTree[index];
      lazyTree[index] = 0;

      // If not at a leaf, propagate to children
      if(left != right) {
	lazyTree[2*index + 1] += change;
	lazyTree[2*index + 2] += change;
      }
    }
    
    // Complete overlap
    if(left >= qleft && right <= qright) {
      tree[index] += delta;

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

      tree[index] = min(tree[2*index + 1], tree[2*index + 2]);
    }
  }

  int rmq(int qleft, int qright) {
    return rmq(qleft, qright, 0, N - 1, 0);
  }

  int rmq(int qleft, int qright, int left, int right, int index) {
    // If changes at this node haven't been updated
    if(lazyTree[index] != 0) {
      int change = lazyTree[index];
      tree[index] += lazyTree[index];
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
      return INT_MAX;
    }
    // Partial
    int mid = (left + right)/2;
    return min(rmq(qleft, qright, left, mid, 2*index + 1),
	       rmq(qleft, qright, mid + 1, right, 2*index + 2));
  }

  void createTree(vector<int>& arr, int left, int right, int index) {
    // Leaf
    if(left == right) {
      tree[index] = arr[left];
    }
    // Non-leaf
    else {
      int mid = (left + right)/2;
      createTree(arr, left, mid, 2*index + 1);
      createTree(arr, mid + 1, right, 2*index + 2);
      tree[index] = min(tree[2*index + 1], tree[2*index + 2]);
    }
  }
  
  segmentTree(vector<int>& arr) {
    N = arr.size();

    // Find next highest 2^x - 1
    int start = 2;
    while((start - 1) < 2*N) start *= 2;
    size = start - 1;

    // Create space, initialize to INT_MAX for RMQ
    tree = new int[size];
    for(int i = 0; i < size; i++) {
      tree[i] = INT_MAX;
    }
    // Same for lazy tree, init to 0
    lazyTree = new int[size];
    memset(lazyTree, 0, size*sizeof(int));

    // Create tree
    createTree(arr, 0, N - 1, 0);
  }
};

int main() {
  // Testing
  vector<int> test = {-23, 15, -44, -34, 100, -1000, 2323, -3, 0, 895};

  segmentTree tree = segmentTree(test);
  tree.printTree();
  tree.update(0, 4, -10);
  cout << tree.rmq(6, 7) << ' ' << tree.rmq(0, 3) << '\n';
  tree.update(0, 9, 105);
  cout << tree.rmq(8, 9) << ' ' << tree.rmq(0, 9) << ' ' << tree.rmq(0, 4) << '\n';
  return 0;
}
