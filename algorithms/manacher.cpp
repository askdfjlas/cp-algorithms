#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define mp make_pair
typedef long long ll;
typedef pair<int,int> iPair;

// Manacher's algorithm for longest palindromic substring
// Returns a vector of maximum expansion lengths for the modified string
vector<int> manacher(string& s) {
  string build = "#";
  FOR(i,s.length()) {
    build += s[i];
    build += '#';
  }      
  vector<int> P(build.length());
  P[0] = 0;
        
  int left = 0;
  int right = 0;
  int cent = 0;
  for(int i = 1; i < build.length(); i++) {
    int revInd = 2*cent - i;
    if(i > right || i + P[revInd] == right) {
      int newLeft = i > right ? i - 1 : i - P[revInd] - 1;
      int newRight = i > right ? i + 1 : right + 1;
                
      while(newLeft >= 0 && newRight < build.length()) {
	if(build[newLeft] != build[newRight]) break;
	newLeft--;
	newRight++;
      }
      if(newRight > right + 1) {
	right = newRight - 1;
	left = newLeft + 1;
	cent = i;
      }
      P[i] = newRight - i - 1;
    }
    else P[i] = min(P[revInd], right - i);
  }
        
  return P;
}

// Testing
int main() {
  string s = "baaabaaa";
  vector<int> res = manacher(s);
  for(auto v : res) cout << v << ' ';
  cout << '\n';
}
