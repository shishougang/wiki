#include <iostream>

using namespace std;

int Merge(int *arr, int *temp, int left, int mid, int right) {
  int i, j, k;
  int inv_count = 0;

  i = left;
  j = mid;
  k = left;
  while ((i <= mid - 1) && (j <= right)) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
      inv_count += (mid - i);
    }
  }
  while (i <= mid - 1) {
    temp[k++] = arr[i++];
  }
  while (j <= right) {
    temp[k++] = arr[j++];
  }
  for (i = left; i <= right; ++i) {
    arr[i] = temp[i];
  }
  return inv_count;
}

int MergeSortHelper(int *arr, int *temp, int left, int right) {
  if (left >= right) {
    return 0;
  }
  int mid = (left + right) / 2;
  int inv_count;
  inv_count = MergeSortHelper(arr, temp, left, mid);
  inv_count += MergeSortHelper(arr, temp, mid + 1, right);
  inv_count += Merge(arr, temp, left, mid + 1, right);
  return inv_count;
}

int MergeSort(int *arr, int size) {
  int *temp = new int[size];
  return MergeSortHelper(arr, temp, 0, size - 1);
}

int main(int argv, char** args) {
  int arr[] = {1, 20, 6, 4, 5};
  cout << "Number of inversions are " << MergeSort(arr, 5) << endl;
  return 0;
}
