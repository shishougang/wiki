#include <iostream>  // NOLINT
using std::cout;
using std::endl;
#include <utility>
using std::swap;
#include <cstdlib>

int randint(int m, int n) {
  return m + (rand() / (RAND_MAX / (n - m + 1) + 1));
}

void SiftDown(int *x, int l, int u) {
  int i = l;
  int child;
  for (;;) {
    child = i * 2;
    if (child > u) {
      break;
    }
    if (child + 1 <= u) {
      if (x[child + 1] < x[child]) {
        child++;
      }
    }
    if (x[i] <= x[child]) {
      break;
    }
    swap(x[i], x[child]);
    i = child;
  }
}

void HeapSort(int *x, int n) {
  int i;
  for (i = n / 2; i >= 1; --i) {
    SiftDown(x, i, n);
  }
  for (i = n; i >= 2; --i) {
    swap(x[1], x[i]);
    SiftDown(x, 1, i - 1);
  }
}

int main(int argc, char *argv[]) {
  const int kMaxN = 10;
  int array[kMaxN + 1];
  int i;
  for (i = 1; i <= kMaxN; ++i) {
    array[i] = randint(0, 100);
  }
  HeapSort(array, kMaxN);
  for (i = 1; i <= kMaxN; ++i) {
    cout << array[i] << " ";
  }
  cout << endl;
  return 0;
}
