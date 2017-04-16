#include<iostream>
#include<algorithm>
#include<climits>

using namespace std;

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int FindMedian(int *arr, int n) {
  sort(arr, arr + n);
  return arr[n/2];
}

int Partition(int *arr, int l, int r, int x) {
  // Search for x in arr[l..r] and move it to end
  int i;
  for (i = l; i < r; ++i) {
    if (arr[i] == x) {
      break;
    }
  }
  swap(&arr[i], &arr[r]);
  i = l;
  for (int j = l; j < r; ++j) {
    if (arr[j] <= x) {
      swap(&arr[i], &arr[j]);
      ++i;
    }
  }
  swap(&arr[i], &arr[r]);
  return i;
}

int KthSmallest(int *arr, int l, int r, int k) {
  if (k > 0 && k <= r - l + 1) {
    int n = r - l + 1;
    int i, median[(n+4)/5];
    for (i = 0; i < n / 5; ++i) {
      median[i] = FindMedian(arr + l + i * 5, 5);
    }
    if (i * 5 < n) {
      median[i] = FindMedian(arr + l + i * 5, n % 5);
      ++i;
    }
    int med_of_med = (i == 1) ? median[i-1] :
                     KthSmallest(median, 0, i - 1, i / 2);
    int pos = Partition(arr, l, r, med_of_med);
    if (pos-l == k-1) {
      return arr[pos];
    }
    if (pos-l > k-1) {
      return KthSmallest(arr, l, pos-1, k);
    }
    return KthSmallest(arr, pos+1, r, k-pos+l-1);
  }
  return INT_MAX;
}

int main() {
  int arr[] = {12, 3, 5, 7, 4, 19, 26};
  int n = sizeof(arr) / sizeof(arr[0]);
  int k = 3;
  cout << "K'th smallest element is "
       << KthSmallest(arr, 0, n-1, k);
  return 0;
}

