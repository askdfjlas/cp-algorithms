#include <bits/stdc++.h>
using namespace std;
#define FOR(x,n) for(int x=0;x<n;x++)

int* computeLPS(string pat) {
  int* lps = new int[pat.length()];
  lps[0] = 0;
  int len = 0;
  int i = 1;
  
  while(i < pat.length()) {
    if(pat[len] == pat[i]) {
      len++;
      lps[i] = len;
      i++;
    }
    else if(len == 0) {
      lps[i] = 0;
      i++;
    }
    else len = lps[len - 1];
  }

  return lps;
}

vector<int> kmp(string search, string pat) {
  vector<int> found;
  int* lps = computeLPS(pat);
  int i = 0, j = 0;
  
  while(i < search.length()) {
    if(search[i] == pat[j]) {
      i++;
      j++;
      if(j == pat.length()) {
	found.push_back(i - j);
	j = lps[j - 1];
      }
    }
    else {
      if(j != 0) j = lps[j - 1];
      else i++;
    }
  }
  
  return found;
}

int main() {
  string pat = "aaaa";
  string search = "aaaaaaabaaaa";

  vector<int> pos = kmp(search, pat);
  for(auto p : pos) cout << p << ' ';
  cout << '\n';
}
