#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define mp make_pair
typedef long long ll;
typedef pair<int,int> iPair;

const int LEFT = 0;
const int RIGHT = 1;
const int COL = 2;

struct Point {
  int x;
  int y;
  Point(int a, int b) {
    x = a;
    y = b;
  }
};

struct Segment {
  Point p1 = Point(-1, -1);
  Point p2 = Point(-1, -1);
  Segment(int x1, int y1, int x2, int y2) {
    p1 = Point(x1, y1);
    p2 = Point(x2, y2);
  }
};

int orient(Point p1, Point p2, Point p3) {
  int res = (p2.x - p1.x)*(p3.y - p2.y) - (p2.y - p1.y)*(p3.x - p2.x);
  if(res == 0) return COL;
  if(res > 0) return LEFT;
  return RIGHT;
}

bool isect(Segment s1, Segment s2) {
  int o1 = orient(s1.p1, s1.p2, s2.p1);
  int o2 = orient(s1.p1, s1.p2, s2.p2);
  int o3 = orient(s2.p1, s2.p2, s1.p1);
  int o4 = orient(s2.p1, s2.p2, s1.p2);

  if(o1 != o2 && o3 != o4) return true;
  if(o1 == COL && o2 == COL)  {
    int l1 = min(s1.p1.x, s1.p2.x);
    int r1 = max(s1.p1.x, s1.p2.x);
    int l2 = min(s2.p1.x, s2.p2.x);
    int r2 = max(s2.p1.x, s2.p2.x);
    
    int d1 = min(s1.p1.y, s1.p2.y);
    int u1 = max(s1.p1.y, s1.p2.y);
    int d2 = min(s2.p1.y, s2.p2.y);
    int u2 = max(s2.p1.y, s2.p2.y);

    if(((l2 >= l1 && l2 <= r1) || (l1 >= l2 && l1 <= r2)) && ((d2 >= d1 && d2 <= u1) || (d1 >= d2 && d1 <= u2))) return true;
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  Segment s1 = Segment(0, 0, 0, 10);
  Segment s2 = Segment(0, 10, 0, 15);

  cout << isect(s1, s2) << '\n';
}
