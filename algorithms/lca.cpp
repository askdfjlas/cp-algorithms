#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define mp make_pair
typedef long long ll;
typedef pair<int,int> iPair;

const int N = 1000;
const int L2N = 9;

vector<int> euler;
vector<int> depths;
int firstOccurrence[N];
int st[2*N][L2N + 2];
int L2[2*N];
int POW2[L2N + 2];

void precomp() {
  int curr = 1;
  int pow = 0;
  POW2[0] = 1;
  for(int i = 1; i < 2*N; i++) {
    if(i == (curr << 1)) {
      curr <<= 1;
      pow++;
      POW2[pow] = curr;
    }
    L2[i] = pow;
  }
}

void eulerTour(vector<int> *adj, int curr, int depth) {
  if(firstOccurrence[curr] == -1) firstOccurrence[curr] = depths.size();
  depths.push_back(depth);
  euler.push_back(curr);
  for(auto v : adj[curr]) {
    eulerTour(adj, v, depth + 1);
    depths.push_back(depth);
    euler.push_back(curr);
  }
}

void makeSt() {
  int l = depths.size();
  FOR(i,l) st[i][0] = i;
  for(int i = 1; i <= L2[l]; i++) {
    int len = POW2[i];
    FOR(j,l - len + 1) {
      int i1 = st[j][i - 1];
      int i2 = st[j + (len >> 1)][i - 1];
      if(depths[i1] < depths[i2]) st[j][i] = i1;
      else st[j][i] = i2;
    }
  }
}

int lca(int a, int b) {
  int l = min(firstOccurrence[a], firstOccurrence[b]);
  int r = max(firstOccurrence[a], firstOccurrence[b]);
  int len = r - l + 1;

  int i1 = st[l][L2[len]];
  int i2 = st[r - POW2[L2[len]] + 1][L2[len]];

  if(depths[i1] < depths[i2]) return euler[i1];
  return euler[i2];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  memset(firstOccurrence, -1, sizeof firstOccurrence);

  // Example taken from www.geeksforgeeks.org/lca-n-ary-tree-constant-query-o1/
  vector<int> adj[9];
  adj[1] = {2, 3};
  adj[2] = {4, 5, 6};
  adj[3] = {7, 8};

  precomp();
  eulerTour(adj, 1, 0);
  makeSt();

  cout << "LCA(6, 7) : " << lca(6, 7) << '\n';
  cout << "LCA(6, 4) : " << lca(6, 4) << '\n';
  cout << "LCA(7, 7) : " << lca(7, 7) << '\n';
  cout << "LCA(1, 2) : " << lca(1, 2) << '\n';
}
