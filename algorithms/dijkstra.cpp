#include <bits/stdc++.h>
#define mp make_pair
#define FOR(x,n) for(int x=0;x<n;x++)
using namespace std;
typedef pair<int,int> iPair;

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

  vector<int> dijkstra(int start) {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    vector<int> distances(n, INT_MAX);
    distances[start] = 0;
    
    pq.push(mp(0, start));
    while(!pq.empty()) {
      auto pair = pq.top();
      int dist = pair.first;
      int next = pair.second;
      pq.pop();

      if(dist > distances[next]) continue;
      for(auto& v : adjList[next]) {
	if((dist + v.second) < distances[v.first]) {
	  distances[v.first] = dist + v.second;
	  pq.push(mp(dist + v.second, v.first));
	}
      }
    }

    return distances;
  }
  
  weightedGraph(int nodes) {
    n = nodes;
    adjList = new vector<pair<int,int>>[n];
  }
};

int main() {
  weightedGraph G = weightedGraph(9);
  
  G.addEdge(0, 1, 4); 
  G.addEdge(0, 7, 8); 
  G.addEdge(1, 2, 8); 
  G.addEdge(1, 7, 11); 
  G.addEdge(2, 3, 7); 
  G.addEdge(2, 8, 2); 
  G.addEdge(2, 5, 4); 
  G.addEdge(3, 4, 9); 
  G.addEdge(3, 5, 14); 
  G.addEdge(4, 5, 10); 
  G.addEdge(5, 6, 2); 
  G.addEdge(6, 7, 1); 
  G.addEdge(6, 8, 6); 
  G.addEdge(7, 8, 7);

  vector<int> dists = G.dijkstra(0);
  FOR(i,9) {
    cout << "Distance from source vertex to " << i << ": " << dists[i] << '\n';
  }
}
