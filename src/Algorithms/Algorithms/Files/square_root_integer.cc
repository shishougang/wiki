#include <iostream>

using namespace std;

int FloorSqrt(int x) {
  if (x == 0 || x == 1) {
    return x;
  }

  int start = 1, end = x;
  int ans;
  while (start <= end) {
    int mid = (start + end) / 2;
    int square = mid * mid;
    if (square == x) {
      return mid;
    }
    if (square < x) {
      start = mid + 1;
      ans = mid;
    } else {
      end = mid - 1;
    }
  }
  return ans;
}

int main() {
  int x = 11;
  cout << FloorSqrt(x) << endl;
  return 0;   
}
    
