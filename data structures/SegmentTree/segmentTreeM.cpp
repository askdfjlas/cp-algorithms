#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define mp make_pair
typedef long long ll;
typedef pair<int,int> iPair;

#define SEGTYPE ll
#define SEGFN min
#define SEGMX LLONG_MAX   // Change to INT_MIN or LLONG_MIN for range max query

class segmentTree {
public:
  SEGTYPE* tree;
  SEGTYPE* lazyTree;
  int N;
  int size;

  void update(int qleft, int qright, SEGTYPE delta) {
    update(qleft, qright, delta, 0, N - 1, 0);
  }
  void update(int qleft, int qright, SEGTYPE delta, int left, int right, int index) {
    if(lazyTree[index] != 0) {
      SEGTYPE change = lazyTree[index];
      tree[index] += lazyTree[index];
      lazyTree[index] = 0;
      if(left != right) {
	lazyTree[2*index + 1] += change;
	lazyTree[2*index + 2] += change;
      }
    }
    if(left >= qleft && right <= qright) {
      tree[index] += delta;
      if(left != right) {
	lazyTree[2*index + 1] += delta;
	lazyTree[2*index + 2] += delta;  
      }
    }
    else if(!(right < qleft || left > qright)) {
      int mid = (left + right)/2;
      update(qleft, qright, delta, left, mid, 2*index + 1);
      update(qleft, qright, delta, mid + 1, right, 2*index + 2);
      tree[index] = SEGFN(tree[2*index + 1], tree[2*index + 2]);
    }
  }
  SEGTYPE rmq(int qleft, int qright) {
    return rmq(qleft, qright, 0, N - 1, 0);
  }
  SEGTYPE rmq(int qleft, int qright, int left, int right, int index) {
    if(lazyTree[index] != 0) {
      SEGTYPE change = lazyTree[index];
      tree[index] += lazyTree[index];
      lazyTree[index] = 0;

      if(left != right) {
	lazyTree[2*index + 1] += change;
	lazyTree[2*index + 2] += change;
      }
    }
    if(left >= qleft && right <= qright)
      return tree[index];
    if(right < qleft || left > qright)
      return SEGMX;
    int mid = (left + right)/2;
    return SEGFN(rmq(qleft, qright, left, mid, 2*index + 1),
	       rmq(qleft, qright, mid + 1, right, 2*index + 2));
  }
  void createTree(vector<SEGTYPE>& arr, int left, int right, int index) {
    if(left == right)
      tree[index] = arr[left];
    else {
      int mid = (left + right)/2;
      createTree(arr, left, mid, 2*index + 1);
      createTree(arr, mid + 1, right, 2*index + 2);
      tree[index] = SEGFN(tree[2*index + 1], tree[2*index + 2]);
    }
  }
  segmentTree(vector<SEGTYPE>& arr) {
    N = arr.size();
    int start = 2;
    while((start - 1) < 2*N) start *= 2;
    size = start - 1;
    tree = new SEGTYPE[size];
    for(int i = 0; i < size; i++)
      tree[i] = SEGMX;
    lazyTree = new SEGTYPE[size];
    memset(lazyTree, 0, size*sizeof(SEGTYPE));
    createTree(arr, 0, N - 1, 0);
  }
  segmentTree(int sz) {
    N = sz;
    int start = 2;
    while((start - 1) < 2*N) start *= 2;
    size = start - 1;
    tree = new SEGTYPE[size];
    for(int i = 0; i < size; i++)
      tree[i] = SEGMX;
    lazyTree = new SEGTYPE[size];
    memset(lazyTree, 0, size*sizeof(SEGTYPE));
  }
};
