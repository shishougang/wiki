#include <iostream>

using namespace std;

int Median(int *arr, int n) {
  if (n % 2 == 0) {
    return (arr[n/2-1] + arr[n/2]) / 2;
  }
  return arr[n/2];
}

int GetMedian(int *arr1, int *arr2, int n) {
  if (n <= 0) {
    return -1;
  }
  if (n == 1) {
    return (arr1[0] + arr2[0]) / 2;
  }
  if (n == 2) {
    return (max(arr1[0] , arr2[0]) + min(arr1[1], arr2[1])) / 2;
  }
  int m1 = Median(arr1, n);
  int m2 = Median(arr2, n);
  if (m1 == m2) {
    return (m1 + m2) / 2;
  }
  if (m1 < m2) {
    // in arr1[m1, n] and arr2[0, m2]
    if (n % 2 == 0) {
      return GetMedian(arr1 + n/2-1, arr2, n - n/2 + 1);
    }
    return GetMedian(arr1 + n/2, arr2, n - n/2);
  }
  // m1 > m2: arr1[0, m1] and arr2[m2, n]
  if (n % 2 == 0) {
    return GetMedian(arr1, arr2 + n/2-1, n - n/2 + 1);
  }
  return GetMedian(arr1, arr2 + n/2, n - n/2);
}

int main() {
  int ar1[] = {1, 2, 3, 6};
  int ar2[] = {4, 6, 8, 10};
  int n1 = sizeof(ar1) / sizeof(ar1[0]);
  int n2 = sizeof(ar2) / sizeof(ar2[0]);
  if (n1 == n2) {
    cout << "Median is " << GetMedian(ar1, ar2, n1) << endl;
  } else
    cout << "Doesn't work for arrays of unequal size" << endl;
  return 0;
}
