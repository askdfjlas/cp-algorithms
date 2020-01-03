#include <bits/stdc++.h>
using namespace std;

class fenwickTree {
public:
  int* tree;
  int size;

  void printTree() {
    for(int i = 0; i <= size; i++) {
      cout << tree[i] << ' ';
    }
    cout << '\n';
  }

  int prefixSum(int index) {
    index++;  // dummy node indexing
    int ret = 0;
    while(index > 0) {
      ret += tree[index];
      index -= (index & -index);
    }
    return ret;
  }

  void update(int index, int delta) {
    index++;  // dummy node indexing
    while(index <= size) {
      tree[index] += delta;
      index += (index & -index); 
    }
  }

  fenwickTree(vector<int>& arr) {
    size = arr.size();
    tree = new int[size+1];  // +1 for dummy node at 0
    memset(tree, 0, sizeof(int)*(size+1));

    for(int i = 0; i < size; i++) {
      update(i, arr[i]); 
    }
  }
};

int main() {
  // Testing
  vector<int> test = {-23, 88, 15, 99, 100, -1000, 2323, -3, 0, 895};

  fenwickTree tree = fenwickTree(test);
  tree.printTree();

  cout << tree.prefixSum(0) << ' ' << tree.prefixSum(5) << ' ' << tree.prefixSum(8) << '\n';
  tree.update(0, 100);
  cout << tree.prefixSum(5) << ' ' << tree.prefixSum(8) << '\n';
  tree.update(8, -5235);
  cout << tree.prefixSum(5) << ' ' << tree.prefixSum(8) << '\n';
}
