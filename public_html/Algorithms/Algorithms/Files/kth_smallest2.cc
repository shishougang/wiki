#include<iostream>
#include<climits>
using namespace std;

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

class MinHeap {
 public:
  MinHeap(int *a, int size);
  void MinHeapify(int i); //To minheapify subtree rooted with index i
  int Parent(int i) {
    return (i - 1) / 2;
  }
  int Left(int i) {
    return (2 * i + 1);
  }
  int Right(int i) {
    return (2 * i + 2);
  }
  int ExtractMin();
  int GetMin() {
    return harr[0];
  }
  
 private:
  int *harr;
  int heap_size;
};

MinHeap::MinHeap(int *a, int size) {
  heap_size = size;
  harr = a;
  int i = (heap_size - 1)/2;
  while (i >= 0) {
    MinHeapify(i);
    i--;
  }
}

void MinHeap::MinHeapify(int i) {
  int l = Left(i);
  int r = Right(i);
  int smallest = i;
  if (l < heap_size && harr[l] < harr[i]) {
    smallest = l;
  }
  if (r < heap_size && harr[r] < harr[smallest]) {
    smallest = r;
  }
  if (smallest != i) {
    swap(&harr[i], &harr[smallest]);
    MinHeapify(smallest);
  }
}

int MinHeap::ExtractMin() {
  if (heap_size == 0) {
    return INT_MAX;
  }
  int root = harr[0];
  if (heap_size > 1) {
    harr[0] = harr[heap_size-1];
    MinHeapify(0);
  }
  heap_size--;
  return root;
}

int KthSmallest(int arr[], int n, int k) {
  MinHeap mh(arr, n);
  for (int i=0; i<k-1; i++) {
    mh.ExtractMin();
  }
  return mh.GetMin();
}
 
int main() {
  int arr[] = {12, 3, 5, 7, 19};
  int n = sizeof(arr) / sizeof(arr[0]), k = 2;
  cout << "K'th smallest element is " << KthSmallest(arr, n, k);
  return 0;
}
