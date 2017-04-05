#include <iostream>
using namespace std;

unsigned int RussianPeasant(unsigned int a, unsigned int b) {
  unsigned int res = 0;
  while (b > 0) {
    if (b & 1) {
      res += a;
    }
    a <<= 1;
    b >>= 1;
  }
  return res;
}

int main() {
  cout << RussianPeasant(18, 1) << endl;
  cout << RussianPeasant(20, 12) << endl;
  return 0;
}
