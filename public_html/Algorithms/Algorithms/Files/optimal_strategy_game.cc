#include <iostream>

using namespace std;

int OptimalStrategyOfGame(int *arr, int n) {

}

int main() {
  int arr1[] = {8, 15, 3, 7};
  int n = sizeof(arr1)/sizeof(arr1[0]);
  cout << optimalStrategyOfGame(arr1, n) << endl;

  int arr2[] = {2, 2, 2, 2};
  n = sizeof(arr2)/sizeof(arr2[0]);
  cout << optimalStrategyOfGame(arr2, n) << endl;

  int arr3[] = {20, 30, 2, 2, 2, 10};
  n = sizeof(arr3)/sizeof(arr3[0]);
  cout << optimalStrategyOfGame(arr3, n) << endl;
  return 0;
}
