#include <iostream>

using namespace std;

int SumBitDifferences(int *arr, int n) {
  int ret = 0;
  for (int i = 0; i < 32; ++i) {
    int count = 0;
    for (int j = 0; j < n; ++j) {
      if (arr[j] & (1 << i)) {
        ++count;
      }
    }
    ret += (count * (n - count) * 2);
  }
  return ret;
}

int main() {
  int arr[] = {1, 3, 5};
  int n = sizeof arr / sizeof arr[0];
  cout << SumBitDifferences(arr, n) << endl;
  return 0;
}
