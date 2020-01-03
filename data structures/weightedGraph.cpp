#include <bits/stdc++.h>
#define mp make_pair
#define FOR(x,n) for(int x=0;x<n;x++)

using namespace std;

class weightedGraph {
public:
  int n;
  vector<pair<int,int>>* adjList;

  void print() {
    FOR(i,n) {
      cout << i << ": ";
      FOR(j,adjList[i].size()) {
	cout << "(" << adjList[i][j].first << ", " << adjList[i][j].second << ") ";
      }
      cout << '\n';
    }
  }

  void addEdge(int a, int b, int weight) {
    adjList[a].push_back(mp(b, weight));
    adjList[b].push_back(mp(a, weight));
  }
  
  weightedGraph(int nodes) {
    n = nodes;
    adjList = new vector<pair<int,int>>[n];
  }
};

int main() {
  weightedGraph G = weightedGraph(5);
  G.addEdge(0, 1, 2);
  G.addEdge(1, 2, 4);
  G.addEdge(2, 3, 8);
  G.addEdge(3, 4, 16);
  G.addEdge(4, 1, 32);
  G.print();
}
