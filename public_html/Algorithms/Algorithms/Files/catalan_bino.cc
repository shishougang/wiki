#include <iostream>

using namespace std;

unsigned long BinomialCoeff(unsigned int n, unsigned int k) {
  unsigned long res = 1;
  // Since C(n, k) = C(n, n-k)
  if (k > n - k) {
    k = n - k;
  }
  // Calculate value of [n*(n-1)*---*(n-k+1)] / [k*(k-1)*---*1]
  for (int i = 0; i < k; ++i) {
    res *= (n - i);
    res /= (i + 1);
  }
  return res;
}

unsigned long Catalan(unsigned int n) {
  unsigned long c = BinomialCoeff(2*n, n);
  return c / (n + 1);
}

int main() {
  for (int i = 0; i < 10; i++) {
    cout << Catalan(i) << " ";
  }
  cout << endl;
  return 0;
}
