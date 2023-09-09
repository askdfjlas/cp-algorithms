#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define FORR(x,a,b) for(int x=a;x<=b;x++)
using ll = long long;
using ii = pair<int,int>;

const int MX = 1e7 + 10;
vector<int> primes, minp(MX);

void lin_sieve() {
  FORR(i,2,MX-1) {
    if(!minp[i]) {
      minp[i] = i;
      primes.push_back(i);
    }
    for(int p : primes) {
      if(p > minp[i] || p * i >= MX) break;
      minp[p * i] = p; 
    }
  }
}