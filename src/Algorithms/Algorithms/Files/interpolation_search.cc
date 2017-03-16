#include <iostream>

using namespace std;

int InterpolationSearch(int *arr, int n, int x) {
  int lo = 0, hi = n - 1;
  while ((lo <= hi) && (x >= arr[lo]) &&
         (x <= arr[hi])) {
    int pos = lo + ((double)(hi - lo) /
                    (arr[hi] - arr[lo]) * (x - arr[lo]));
    if (arr[pos] == x) {
      return pos;
    } else if (arr[pos] < x) {
      lo = pos + 1;
    } else {
      hi = pos - 1;
    }
  }
  return -1;
}

int main() {
  int arr[] =  {10, 12, 13, 16, 18, 19, 20, 21, 22, 23,
                24, 33, 35, 42, 47};
  int n = sizeof(arr) / sizeof(arr[0]);
  int x = 18;
  int index = InterpolationSearch(arr, n, x);

  if (index != -1) {
    cout << "Element found at index " << index << endl;
  } else {
    cout << "Element not found." << endl;
  }
  return 0;
}
