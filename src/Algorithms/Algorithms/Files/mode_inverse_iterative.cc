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

int main() {
  int a = 3, m = 11;
  cout << "Modular multiplicative inverse is " <<
      ModInverse(a, m) << endl;
  return 0;
}
