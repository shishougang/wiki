#include <iostream>
#include <cstdio>

using namespace std;

int EdulerTotient(int n) {
  float res = n;
  for (int p = 2; p * p <= n; ++p) {
    if (n % p == 0) {
      while (n % p == 0) {
        n /= p;
      }
      res *= (1.0 - (1.0 / (float)p));
    }
  }
  if (n > 1) {
    res *= (1.0 - (1.0 / (float) n));
  }
  return (int)res;
}

int EdulerTotient1(int n) {
  int res = n;
  for (int p = 2; p * p <= n; ++p) {
    if (n % p == 0) {
      while (n % p == 0) {
        n /= p;
      }
      res -= res / p;
    }
  }
  if (n > 1) {
    res -= res / n;
  }
  return res;
}

int main() {
  int n;
  for (n = 1; n <= 10; n++) {
    printf("phi(%d) = %d\n", n, EdulerTotient(n));
    printf("phi(%d) = %d\n", n, EdulerTotient1(n));
  }
  return 0;
}
