#include <bits/stdc++.h>
using namespace std;

int gcd_extend(int a, int b, int* x, int* y) {
  if(a == 0) {
    *x = 0;
    *y = 1;
    
    return b;
  }

  int gcd = gcd_extend(b % a, a, x, y);
  int temp = *x;
  *x = *y - (b/a)*(*x);
  *y = temp;
  
  return gcd;
}

int main() {
  // Testing
  int  a[] = {10, 100, 47, 9999, 3482, 0};
  int b[] = {5, 95, 46, 333, 5760, 0};
  int size = sizeof(a)/sizeof(int);

  for(int i = 0; i < size; i++) {
    cout << "a = " << a[i] << ", b = " << b[i] << '\n';
    int x, y;
    int gcd = gcd_extend(a[i], b[i], &x, &y);

    cout << x << '*' << a[i] << " + " << y << '*' << b[i] << " = " << gcd << '\n';
  }
  
  return 0;
}
