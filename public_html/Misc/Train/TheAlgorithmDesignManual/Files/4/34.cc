#include <iostream>  // NOLINT
using std::cout;
using std::endl;

int FindMissingElement(int *array, int l, int h) {
  while (l <= h) {
    int mid = (l + h) / 2;
    if (array[mid] > (mid + 1)) {
      h = mid - 1;
    } else if (array[mid] <= (mid + 1)) {
      l = mid + 1;
    }
  }
  return l + 1;
}

int main(int argc, char *argv[]) {
  int array[6] = {1,2,3,6,7,8};
  cout << FindMissingElement(array, 0, 5) << endl;
  return 0;
}
