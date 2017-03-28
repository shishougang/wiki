#include <iostream>

using namespace std;

int NthMagicNum(int n) {
  int pow = 1, answer = 0;
  while (n) {
    pow *= 5;
    if (n & 1) {
      answer += pow;
    }
    n >>= 1;
  }
  return answer;
}

int main() {
  int n = 5;
  cout << "5th magic number is " << NthMagicNum(n) << endl;
  return 0;
}
