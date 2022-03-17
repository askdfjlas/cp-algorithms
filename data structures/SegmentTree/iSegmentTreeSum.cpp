#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define mp make_pair
#define PI 3.14159265358979323846264338327950288
typedef long long ll;
typedef pair<int,int> ii;

#define SEGTYPE ll

class Vertex {
public:
  SEGTYPE val, lazyVal = 0;
  Vertex* left = NULL, * right = NULL;
  void createChildren(int l, int r) {
    int mid = (l + r)/2;
    SEGTYPE sval = val/(r - l + 1);
    this->left = new Vertex(l, mid, (SEGTYPE)(mid - l + 1) * sval);
    this->right = new Vertex(mid + 1, r, (SEGTYPE)(r - mid) * sval);
  }
  void flush(int l, int r) {
    if(!left && l != r) createChildren(l, r);
    if(left) {left->lazyVal += lazyVal; right->lazyVal += lazyVal;}
    val += (SEGTYPE)(r - l + 1) * lazyVal;
    lazyVal = 0;
  }
  Vertex(int l, int r, SEGTYPE sval) {val = (SEGTYPE)(r - l + 1) * sval;}
};

class segmentTree {
public:
  int lo, hi;
  Vertex* root;
  SEGTYPE query(Vertex* curr, int ql, int qr, int l, int r) {
    curr->flush(l, r);
    if(l > qr || r < ql) return 0;
    if(l >= ql && r <= qr) return curr->val;
    int mid = (l + r)/2;
    if(!curr->left) curr->createChildren(l, r);
    return query(curr->left, ql, qr, l, mid) + query(curr->right, ql, qr, mid + 1, r);
  }
  SEGTYPE query(int l, int r) {return query(root, l, r, lo, hi);}
  SEGTYPE query(int i) {return query(i, i);}
  void update(Vertex* curr, int ql, int qr, SEGTYPE delta, int l, int r) {
    curr->flush(l, r);
    if(l > qr || r < ql) return;
    if(l >= ql && r <= qr) {
      curr->lazyVal += delta;
      curr->flush(l, r);
      return;
    }
    int mid = (l + r)/2;
    if(!curr->left) curr->createChildren(l, r);
    update(curr->left, ql, qr, delta, l, mid);
    update(curr->right, ql, qr, delta, mid + 1, r);
    curr->val = curr->left->val + curr->right->val;
  }
  void update(int l, int r, SEGTYPE delta) {update(this->root, l, r, delta, lo, hi);}
  void update(int idx, SEGTYPE delta) {update(idx, idx, delta);}
  segmentTree(int lo, int hi) {
    this->lo = lo; 
    this->hi = hi;
    this->root = new Vertex(lo, hi, 0);
  }
};

// https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/E
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  segmentTree tree = segmentTree(0, (int)1e9);

  int big = (int)1e8;
  int n, q;
  cin >> n >> q;
  while(q--) {
    int t;
    cin >> t;
    if(t == 1) {
      int l, r, v;
      cin >> l >> r >> v;
      tree.update(l + big, r + big - 1, v);
    }
    else {
      int i;
      cin >> i;
      cout << tree.query(i + big) << '\n';
    }
  }
}

// UPDATE N WHEN UR DONE AAAAAAAAAAAAAAAAAAAAAAAAAAA (if it applies lol)
