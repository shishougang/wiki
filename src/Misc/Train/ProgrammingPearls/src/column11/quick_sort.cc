#include <iostream> //NOLINT
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

void isort(int *array, int n) {
  int i, j, t;
  for (i = 1; i < n; ++i) {
    t = array[i];
    for (j = i; j >= 0  && array[j - 1] < t; --j) {
      array[j] = array[j - 1];
    }
    array[j - 1] = t;
  }
}

void qsort1(int *array, int l, int u) {
  /*use array[l] for the mid element */
  if (l >= u) {
    return;
  }
  int m;
  m = l;
  for (int i = l + 1; i <= u; ++i) {
    if (array[i] < array[l]) {
      swap(array, ++m, i);
    }
  }
  swap(array, l, m);
  qsort1(array, l, m - 1);
  qsort1(array, m + 1, u);
}

void qsort2(int *array, int l, int u) {
  /*use array[l] for the mid element, from back to start,
    always swap the first element */
  if (l >= u) {
    return;
  }
  int i, m;
  i = m = u + 1;
  do {
    do {
      --i;
    } while (array[i] < array[l]);
    swap(array, --m, i);
  } while (i > l);
  qsort2(array, l, m - 1);
  qsort2(array, m + 1, u);
}

void qsort3(int *array, int l, int u) {
  /* two-way partition, use array[l] for the mid element */
  if (l >= u) {
    return;
  }
  int t, i , j;
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
  qsort3(array, l, j - 1);
  qsort3(array, j + 1, u);
}

const int kCutOff = 50;
void qsort4(int *array, int l, int u) {
  /* qsort3 + randomization + isort small subarrays + swap inline */
  if (u - l < kCutOff) {
    return;
  }
  int t, i , j;
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
  qsort3(array, l, j - 1);
  qsort3(array, j + 1, u);
}

void GenerateRandomArray(int *array, int n, int mod) {
  for (int i = 0; i < n; ++i) {
    array[i] = randint(0, mod - 1);
  }
}

void PrintArray(int *array, int n, char *head) {
  cout << head << endl;
  for (int i = 0; i < n; ++i) {
    cout << array[i]  << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  const int kMaxN = 10;
  int array[kMaxN];
  GenerateRandomArray(array, kMaxN, kMaxN * 10);
  qsort1(array, 0, kMaxN - 1);
  PrintArray(array, kMaxN, "qsort1:");

  GenerateRandomArray(array, kMaxN, kMaxN * 10);
  qsort2(array, 0, kMaxN - 1);
  PrintArray(array, kMaxN, "qsort2:");

  GenerateRandomArray(array, kMaxN, kMaxN * 10);
  qsort3(array, 0, kMaxN - 1);
  PrintArray(array, kMaxN, "qsort3:");

  GenerateRandomArray(array, kMaxN, kMaxN * 10);
  qsort4(array, 0, kMaxN - 1);
  isort(array, kMaxN);
  PrintArray(array, kMaxN, "qsort4:");
  return 0;
}
