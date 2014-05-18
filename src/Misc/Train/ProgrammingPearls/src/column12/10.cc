#include <iostream> // NOLINT
using std::endl;
using std::cout;
#include <cstdlib>

int randint(int m, int n) {
  return m + (rand() / (RAND_MAX / (n - m + 1) + 1));
}

int Select() {
  int res;
  int i = 0;
  res = object[i];
  ++i;
  while (IsEnd(object[i])) {
      int j = randint(0, i);
      if (j < 1) {
        res = object[i];
      }
      ++i;
  }
  return res;
}
