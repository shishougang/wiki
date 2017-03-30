#include <iostream>

using namespace std;

unsigned int GetLeftMostBit(int n) {
  int m = 0;
  while (n > 1) {
    n >>= 1;
    ++m;
  }
  return m;
}

unsigned int CountSetBits(unsigned int n) {
  if (n == 0) {
    return 0;
  }
  int m = GetLeftMostBit(n);
  if (n == (1 << (m + 1) - 1)) {
    return (m + 1) * (1 << m);
  }
  n = n - (1 << m);
  return (n + 1) + CountSetBits(n) + m * (1 << (m - 1));
}

int main() {
  int n = 17;
  cout << "Total set bit count is " << CountSetBits(n) << endl;
  return 0;
}
