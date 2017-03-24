#include <iostream>
#include <cstdio>
using namespace std;

/* ax + by = gcd(a, b) */
int GCDExtended(int a, int b, int *x, int *y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }
  int x1, y1;
  int gcd = GCDExtended(b % a, b, &x1, &y1);
  *x = y1 - (b / a) * x1;
  *y = x1;
  return gcd;
}

int main() {
  int x, y;
  int a = 35, b = 15;
  int g = GCDExtended(a, b, &x, &y);
  printf("gcd(%d, %d) = %d, x = %d, y = %d\n",
         a, b, g, x, y);
  return 0;
}
