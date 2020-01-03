#include <bits/stdc++.h>
using namespace std;

// Fleury's algorithm for finding a Eulerian circuit in an adjacency matrix, this code doesn't check if the graph is Eulerian
// It's O(n^2) when there's a faster solution, but ok for time limit for small graphs

// Find number of reachable nodes using bfs
int reachable(vector<string>& matrix, int start) {
  deque<int> q;
  unordered_set<int> visited;
  q.push_back(start);
  visited.insert(start);

  while(!q.empty()) {
    int curr = q.front();
    q.pop_front();

    for(int i = 0; i < matrix.size(); i++) {
      if(matrix[curr][i] == '1') {
	if(visited.find(i) != visited.end()) continue;  // If seen before
	q.push_back(i);
	visited.insert(i);
      }
    }
  }

  return visited.size();
}

vector<int> fleury(vector<string> matrix, int start) {
  vector<int> res = {start};
  int curr = start;

  while(true) {
    int degree = 0;
    for(int i = 0; i < matrix.size(); i++) if(matrix[curr][i] == '1') degree++;
    if(degree == 0) break;
    for(int i = 0; i < matrix.size(); i++) {
      if(matrix[curr][i] == '1') {
        int tmp1 = reachable(matrix, curr);

    	// Remove edge
    	matrix[curr][i] = '0';
    	matrix[i][curr] = '0';

    	int tmp2 = reachable(matrix, curr);
    	if(tmp1 == tmp2 || degree == 1) {  // Getting rid of only edge is always fine
    	  curr = i;
    	  break;
    	}
    	else {
    	  // Add edges back
    	  matrix[curr][i] = '1';
    	  matrix[i][curr] = '1';
    	}
      }
    }

    res.push_back(curr);
  }

  return res;
}

// Overload, manually finds a node of the connected part (assuming some nodes have degree 0)
vector<int> fleury(vector<string> matrix) {
  for(int i = 0; i < matrix.size(); i++)
    for(int j = 0; j < matrix.size(); j++)
      if(matrix[i][j] == '1') return fleury(matrix, i);
  return {};
}

int main() {
  // Testing, example graph taken from https://www.youtube.com/watch?v=HXNyr2N3euc
  vector<string> test = {"00110", "00011", "10010", "11101", "01010"};
  vector<int> path = fleury(test);
  for(int i = 0; i < path.size(); i++) {
    cout << path[i] << ' ';
  }
}
