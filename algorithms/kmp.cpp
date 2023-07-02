#include <bits/stdc++.h>
using namespace std;
#define FOR(x,n) for(int x=0;x<n;x++)

vector<int> compute_lps(string pat) {
  int n = pat.length(), j = 0;
  vector<int> lps(n);
  for(int i = 1; i < n; i++) {
    if(pat[i] == pat[j] || j == 0) {
      if(pat[i] == pat[j]) j++;
      lps[i] = j;
    }
    else {
      j = lps[j - 1];
      i--;
    }
  }
  return lps;
}

vector<int> kmp(string search, string pat) {
  vector<int> found, lps = compute_lps(pat);
  int i = 0, j = 0;
  while(i < (int)search.length()) {
    if(search[i] == pat[j]) {
      i++;
      j++;
      if(j == (int)pat.length()) {
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
