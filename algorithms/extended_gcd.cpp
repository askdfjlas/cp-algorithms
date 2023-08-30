#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<ll,pair<ll,ll>> extended_gcd(ll a, ll b) {
  if(a == 0) return {b, {0ll, 1ll}};
  ll k = b/a;
  auto [g, sol] = extended_gcd(b - k * a, a);
  auto [c, d] = sol;
  return {g, {d - c * k, c}};
}
