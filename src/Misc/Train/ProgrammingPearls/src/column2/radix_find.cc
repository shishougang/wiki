#include <iostream> // NOLINT
using std::cout;
using std::endl;
#include <utility>
using std::swap;

enum FindErrors {
  kFind = 0,
  kNotFind,
};

FindErrors RadixFindDuplicate(int *array, int n, int *dup_num) {
  for (int i = 0; i < n; ++i) {
    while (i != array[i]) {
      if (array[i] == array[array[i]]) {
        *dup_num = array[i];
        return kFind;
      }
      swap(array[i], array[array[i]]);
    }
  }
  return kNotFind;
}

int main(int argc, char *argv[]) {
  const int kMaxN = 10;
  int a[kMaxN] = {2, 4, 1, 5, 7,  6, 1, 9, 0, 2};
  FindErrors res;
  int duplicate_num;
  res  = RadixFindDuplicate(a, kMaxN, &duplicate_num);
  if (res == kNotFind) {
    cout << "not find duplicate num" << endl;
  } else {
    cout << "one of the duplicate num: " << duplicate_num << endl;
  }
  return 0;
}
