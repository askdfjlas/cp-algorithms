ll mod_exp(ll x, ll y, ll mod) {
    ll res = 1;
    while(y > 0) {
        if(y & 1) res = res*x % mod;
        y >>= 1;
        x = x*x % mod;
    }
    return res;
}