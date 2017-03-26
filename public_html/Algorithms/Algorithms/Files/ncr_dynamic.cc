#include <cstring>
#include <iostream>

using namespace std;

int nCrModP(int n, int r, int p) {
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
  
int main() {
  int n = 10, r = 2, p = 13;
  cout << "Value of nCr % p is " << nCrModP(n, r, p);
  return 0;
}
