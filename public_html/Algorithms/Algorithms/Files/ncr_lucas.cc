#include <cstring>
#include <iostream>

using namespace std;

int nCrModPDP(int n, int r, int p) {
  int C[r+1];
  memset(C, 0, sizeof(C));

  C[0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = min(i, r); j > 0; --j) {
      C[j] = (C[j] + C[j-1]) % p;
    }
  }
  return C[r];
}

int nCrModPLucas(int n, int r, int p) {
  if (r == 0) {
    return 1;
  }
  int ni = n % p;
  int ri = r % p;
  return (nCrModPLucas(n/p, r/p, p) *
          nCrModPDP(ni, ri, p)) % p;
}

int main() {
  int n = 1000, r = 900, p = 13;
  cout << "Value of nCr % p is " << nCrModPLucas(n, r, p);
  return 0;
}
