#include <iostream>
#include <algorithm>

using namespace std;

int GetSum(int *bit_tree, int index) {
  int sum = 0;
  while (index > 0) {
    sum += bit_tree[index];
    index -= index & (-index);
  }
  return sum;
}

void UpdateBit(int *bit_tree, int n, int index, int val) {
  while (index <= n) {
    bit_tree[index] += val;
    index += index & (-index);
  }
}

void Convert(int *arr, int n) {
  int temp[n];
  for (int i = 0; i < n; ++i) {
    temp[i] = arr[i];
  }
  sort(temp, temp + n);
  for (int i = 0; i < n; ++i) {
    arr[i] = lower_bound(temp, temp+n, arr[i]) - temp + 1;
  }
}

int GetInvCount(int *arr, int n) {
  int inv_count = 0;
  Convert(arr, n);
  int Bit[n+1];
  for (int i = 1; i <= n; ++i) {
    Bit[i] = 0;
  }
  for (int i = n - 1; i >= 0; --i) {
    inv_count += GetSum(Bit, arr[i] - 1);
    UpdateBit(Bit, n, arr[i], 1);
  }
  return inv_count;
}

int main() {
  int arr[] = {8, 4, 2, 1};
  int n = sizeof(arr)/sizeof(int);
  cout << "Number of inversions are : " << GetInvCount(arr,n);
  return 0;
}
