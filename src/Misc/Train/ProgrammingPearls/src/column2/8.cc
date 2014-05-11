#include <iostream> // NOLINT
using std::cout;
using std::endl;
#include <utility>
using std::swap;
#include <ctime>
#include <cstdlib>

unsigned int seed = time(NULL);
int randint(int m, int n) {
  return m + rand_r(&seed) / (RAND_MAX / (n + 1 - m) + 1);
}

void RandomSelectionK(int *array, int l, int u, int k) {
  if (l >= u) {
    return;
  }
  swap(array[l], array[randint(l, u)]);
  int pivot = array[l];
  int i = l;
  int j = u + 1;
  while (true) {
    do {
      ++i;
    } while (i <= u && array[i] < pivot);
    do {
      --j;
    } while (array[j] > pivot);
    if (i > j) {
      break;
    }
    swap(array[i], array[j]);
  }
  swap(array[l], array[j]);
  if (j < k) {
    RandomSelectionK(array, j + 1, u, k);
  } else if (j > k) {
    RandomSelectionK(array, l, j - 1, k);
  }
}

int main(int argc, char *argv[]) {
  const int kMaxN = 100;
  const int kSelectK = 8;
  int array[kMaxN];
  for (int i = 0; i < kMaxN; ++i) {
    array[i] = kMaxN - i;
  }
  RandomSelectionK(array, 0, kMaxN - 1, kSelectK);
  cout << "the k minimal elements are:" << endl;
  for (int i = 0; i < kSelectK; ++i) {
    cout << array[i] << " ";
  }
  cout << endl;
  return 0;
}
