#include <iostream>  // NOLINT
using std::cout;
using std::endl;
#include <cstdlib>

void swap(int *array, int m, int n) {
  int temp;
  temp = array[m];
  array[m] = array[n];
  array[n] = temp;
}

int randint(int m, int n) {
  return m + (rand() / (RAND_MAX / (n - m + 1) + 1));
}

void SelectK(int *array, int l, int u, int k) {
  if (l >= u) {
    return;
  }
  int t, i, j;
  swap(array, l, randint(l, u));
  t = array[l];
  i = l;
  j = u + 1;
  for (;;) {
    do {
      ++i;
    } while (i <= u && array[i] < t);
    do {
      --j;
    } while (array[j] > t);
    if (i > j) {
      break;
    }
    swap(array, i, j);
  }
  swap(array, l, j);
  if (j < k) {
    SelectK(array, j + 1, u, k);
  }
  else if (j > k) {
    SelectK(array, l, j - 1, k);
  }
}

int main(int argc, char *argv[]) {
  const int kMaxN = 50;
  const int kKth = 13;
  int x[kMaxN];
  for (int i = 0; i < kMaxN; ++i) {
    x[i] = kMaxN - i;
  }
  SelectK(x, 0, kMaxN - 1, kKth - 1);
  cout << x[kKth - 1] << endl;
  return 0;
}
  
