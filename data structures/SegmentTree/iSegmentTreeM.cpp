#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define mp make_pair
#define PI 3.14159265358979323846264338327950288
typedef long long ll;
typedef pair<int,int> ii;

#define SEGTYPE int
#define SEGFN max
#define SEGMX INT_MIN  // Change to INT_MIN or LLONG_MIN for range max query
#define SEGINIT 1  // 1 => Initialize values to [lo, lo + 1, ..., hi]; works for max and min

struct Vertex {
  SEGTYPE val, lazyVal = 0;
  Vertex* left = NULL, * right = NULL;
  void createChildren(int l, int r) {
    int mid = (l + r)/2;
    this->left = new Vertex(l, mid, this->val - ((SEGINIT && SEGMX < 0) ? r - mid : 0));
    this->right = new Vertex(mid + 1, r, this->val + ((SEGINIT && SEGMX > 0) ? mid + 1 - l : 0));
  }
  void flush(int l, int r) {
    if(!left && l != r) createChildren(l, r);
    if(left) {left->lazyVal += lazyVal; right->lazyVal += lazyVal;}
    val += lazyVal;
    lazyVal = 0;
  }
  Vertex(int l, int r, SEGTYPE sval) {val = sval;}
};

struct SegmentTree {
  int lo, hi;
  Vertex* root;
  SEGTYPE query(Vertex* curr, int ql, int qr, int l, int r) {
    curr->flush(l, r);
    if(l > qr || r < ql) return SEGMX;
    if(l >= ql && r <= qr) return curr->val;
    int mid = (l + r)/2;
    if(!curr->left) curr->createChildren(l, r);
    return SEGFN(query(curr->left, ql, qr, l, mid), query(curr->right, ql, qr, mid + 1, r));
  }
  SEGTYPE query(int l, int r) {return query(root, l, r, lo, hi);}
  SEGTYPE query(int i) {return query(i, i);}
  #if SEGMX < 0
  SEGTYPE lbound(Vertex* curr, int l, int r, SEGTYPE x) {
    curr->flush(l, r);
    if(l == r) return curr->val >= x ? l : l + 1;
    int mid = (l + r)/2;
    curr->left->flush(l, mid);
    return (curr->left->val >= x) ? lbound(curr->left, l, mid, x) : lbound(curr->right, mid + 1, r, x);
  }
  SEGTYPE lbound(SEGTYPE x) {return lbound(root, lo, hi, x);}
  SEGTYPE ubound(SEGTYPE x) {return lbound(x + 1);}
  #endif
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
    curr->val = SEGFN(curr->left->val, curr->right->val);
  }
  void update(int l, int r, SEGTYPE delta) {update(this->root, l, r, delta, lo, hi);}
  void update(int idx, SEGTYPE delta) {update(idx, idx, delta);}
  SegmentTree(int lo, int hi) {
    this->lo = lo; 
    this->hi = hi;
    this->root = new Vertex(lo, hi, (SEGINIT && SEGMX < 0) ? hi : (SEGINIT ? lo : 0));
  }
};

// https://judge.yosupo.jp/problem/staticrmq; ~700ms for N = 5e5
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  int n, q;
  cin >> n >> q;

  SegmentTree tree = SegmentTree(0, (int)5e5+4);
  FOR(i,n) {
    int w;
    cin >> w;
    tree.update(i, w); 
  }

  while(q--) {
    int l, r;
    cin >> l >> r;
    cout << tree.query(l, r - 1) << '\n';
  }
}

// UPDATE N WHEN UR DONE AAAAAAAAAAAAAAAAAAAAAAAAAAA (if it applies lol)
