#include <iostream>

using namespace std;

int GCD(int a, int b) {
  if (a == 0) {
    return b;
  }
  return GCD(b % a, a);
}

// compute x^y under modulo m
int Power(int x, unsigned int y, unsigned int m) {
  if (y == 0) {
    return 1;
  }
  int p = Power(x, y / 2, m) % m;
  p = (p * p) % m;
  return (y % 2 == 0) ? p : (x * p) % m;
}

void ModInverse(int a, int m) {
  int g = GCD(a, m);
  if (g != 1) {
    cout << "Inverse doesn't exist" << endl;
  } else {
    cout << "Modular multiplicative inverse is "
         << Power(a, m-2, m) << endl;
  }
}

int main() {
  int a = 3, m = 11;
  ModInverse(a, m);
  return 0;
}
