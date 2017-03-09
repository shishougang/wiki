#include <iostream>

using namespace std;

int OptimalStrategyOfGame(int *arr, int n) {
  int table[n][n];
  int i, j, gap, x, y, z;

  for (gap = 0; gap < n; ++gap) {
    for (i = 0, j = gap; j < n; ++i, ++j) {
      x = (i+2 <= j) ? table[i+2][j] : 0;
      y = (i+1 <= j-1) ? table[i+1][j-1] : 0;
      z = (i <= j-2) ? table[i][j-2] : 0;
      table[i][j] = max(arr[i] + min(x, y),
                        arr[j] + min(y, z));
    }
  }
  return table[0][n-1];
}

int main() {
  int arr1[] = {8, 15, 3, 7};
  int n = sizeof(arr1)/sizeof(arr1[0]);
  cout << OptimalStrategyOfGame(arr1, n) << endl;

  int arr2[] = {2, 2, 2, 2};
  n = sizeof(arr2)/sizeof(arr2[0]);
  cout << OptimalStrategyOfGame(arr2, n) << endl;

  int arr3[] = {20, 30, 2, 2, 2, 10};
  n = sizeof(arr3)/sizeof(arr3[0]);
  cout << OptimalStrategyOfGame(arr3, n) << endl;
  return 0;
}
