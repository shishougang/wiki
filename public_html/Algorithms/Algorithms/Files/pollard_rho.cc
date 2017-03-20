#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

long ModularPow(long base, int exp, long mod) {
  long res = 1;
  while (exp > 0) {
    if (exp & 1) {
      res = (res * base) % mod;
    }
    exp >>= 1;
    base = (base * base) % mod;
  }
  return res;
}

long GCD(long a, long b) {
  if (a == 0) {
    return b;
  }
  return GCD(b % a, a);
}

long PollardRho(long n) {
  srand(time(NULL));
  // no prime divisor for 1
  if (n == 1) {
    return n;
  }
  if (n % 2 == 0) {
    return 2;
  }
  // pick from the range [2, N)
  long x = (rand() % (n - 2)) + 2;
  long y = x;
  long c = (rand() % (n - 1)) + 1;
  long d = 1;
  while (d == 1) {
    x = (ModularPow(x, 2, n) + c) % n;
    y = (ModularPow(y, 2, n) + c) % n;
    y = (ModularPow(y, 2, n) + c) % n;
    d = GCD(abs(x - y), n);
    if (d == n) {
      return PollardRho(n);
    }
  }
  return d;
}

int main() {
  long n = 10967535067;
  printf("One of the divisors for %ld is %ld.",
         n, PollardRho(n));
  return 0;
}
