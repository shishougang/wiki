#include <iostream>

using namespace std;

int ModInverse(int a, int m) {
  int m0 = m, t, q;
  int x = 0, y = 1;
  if (m == 1) {
    return 0;
  }
  while (m > 0) {
    q = a / m;
    t = m;
    m = a % m;
    a = t;

    t = x;
    x = y - q * x;
    y = t;
  }
  if (y < 0) {
    y += m0;
  }
  return y;
}

int FindMinX(int *num, int *rem, int k) {
  int prod = 1;
  for (int i = 0; i < k; ++i) {
    prod *= num[i];
  }
  int res = 0;
  for (int i = 0; i < k; ++i) {
    int pp = prod / num[i];
    res += rem[i] * ModInverse(pp, num[i]) * pp;
  }
  return res % prod;
}

int main(void) {
  int num[] = {3, 4, 5};
  int rem[] = {2, 3, 1};
  int k = sizeof(num)/sizeof(num[0]);
  cout << "x is " << FindMinX(num, rem, k);
  return 0;
}
