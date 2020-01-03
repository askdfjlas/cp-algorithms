ll gcd_extend(ll a, ll b, ll* x, ll* y) {
  if(a == 0) {
    *x = 0;
    *y = 1;

    return b;
  }

  ll gcd = gcd_extend(b % a, a, x, y);
  ll temp = *x;
  *x = *y - (b/a)*(*x);
  *y = temp;

  return gcd;
}

ll mod_inverse(ll a, ll mod) {
    ll res, tmp;
    gcd_extend(a, mod, &res, &tmp);
    while(res < 0) res += mod;
    return res;
}

// code to find inverse mod, given number a, modulus mod
// adapted from euclid_extend.cpp so no testing, worked to solve an srm problem