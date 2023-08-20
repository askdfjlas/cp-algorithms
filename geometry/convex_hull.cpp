#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define FORR(x,a,b) for(int x=a;x<=b;x++)
using ld = long double;
using ll = long long;
typedef pair<int,int> ii;

constexpr auto eps = 1e-8;
inline int sgn(ld x) { return (abs(x) <= eps) ? 0 : (x < 0 ? -1 : 1); }
inline int sgn(ll x) { return (x == 0) ? 0 : (x < 0 ? -1 : 1); }

template<typename T>
struct _Point {
  T x = 0, y = 0;
  _Point() = default;
  _Point(T x, T y) : x(x), y(y) {}
  bool operator<(const _Point &p) const { return !sgn(p.x - x) ? sgn(y - p.y) < 0 : x < p.x; }
  bool operator==(const _Point &p) const { return !sgn(p.x - x) && !sgn(p.y - y); }
  _Point operator+(const _Point &p) const { return {x + p.x, y + p.y}; }
  _Point operator-(const _Point &p) const { return {x - p.x, y - p.y}; }
  _Point operator*(T a) const { return {x * a, y * a}; }
  _Point operator/(T a) const { return {x / a, y / a}; }
  T operator*(const _Point &p) const { return x * p.x + y * p.y; }  // dot
  T operator^(const _Point &p) const { return x * p.y - y * p.x; }  // cross
  friend auto &operator>>(istream &i, _Point &p) { return i >> p.x >> p.y; }
  friend auto &operator<<(ostream &o, _Point p) { return o << p.x << ' ' << p.y; }
};

using Point = _Point<ll>;

auto dist2(const Point &a) { return a * a; }

template<class RandomIt>
void hull_sort(RandomIt first, RandomIt last, Point origin = Point(0, 0)) {
  auto hull_cmp = [&origin](const Point& p1, const Point& p2) {
    ll cross = (p1 - origin) ^ (p2 - origin);
    return cross ? cross > 0 : dist2(origin - p1) < dist2(origin - p2);
  };
  sort(first, last, hull_cmp);
}

vector<Point> convex_hull(
  vector<Point> &points,
  bool allow_collinear = false,
  bool use_provided_order = false
) { 
  if(!use_provided_order) {
    nth_element(points.begin(), points.begin(), points.end());
    hull_sort(points.begin() + 1, points.end(), points[0]);
  }
  if(allow_collinear) {
    int i = (int)points.size() - 1;
    while(i >= 0 && !sgn((points[i] - points[0]) ^ (points[i] - points.back()))) i--;
    reverse(points.begin() + i + 1, points.end());
  }
  vector<Point> hull;
  for(auto &t : points) {
    for(ll sz = hull.size();
        sz > 1 && (sgn((t - hull[sz - 2]) ^ (hull[sz - 1] - hull[sz - 2])) >= allow_collinear);
        hull.pop_back(), sz = hull.size()) {
    }
    hull.push_back(t);
  }
  return hull;
}

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  int n;
  cin >> n;
  vector<Point> pts(n);
  FOR(i,n) cin >> pts[i];
  int best = 0;
  FOR(i,n) {
    auto p = pts[i];
    if(p.y < pts[best].y) best = i;
    else if(p.y == pts[i].y && p.x < pts[i].x) best = i;
  }
  swap(pts[best], pts[0]);
  hull_sort(pts.begin() + 1, pts.end(), pts[0]);
  auto hull = convex_hull(pts, true, true);
  cout << (int)hull.size() << '\n';
  for(auto p : hull) cout << p << '\n';
}
