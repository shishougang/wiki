#include <iostream>

using namespace std;

int GCDExtended(int a, int b, int *x, int *y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }
  int x1, y1;
  int gcd = GCDExtended(b % a, a, &x1, &y1);
  *x = y1 - (b / a) * x1;
  *y = x1;
  return gcd;
}

void ModInverse(int a, int m) {
  int x, y;
  int g = GCDExtended(a, m, &x, &y);
  if (g != 1) {
    cout << "Inverse doesn't exist" << endl;
  } else {
    // m is added to handle negative x
    int res = (x % m + m) % m;
    cout << "Modular multiplicative inverse is " << res << endl;
  }
}

int main() {
  int a = 3, m = 11;
  ModInverse(a, m);
  return 0;
}

