#include <iostream>  // NOLINT
using std::cout;
using std::endl;

int FindLargestNumber(int *array, int l, int h) {
  if (array[l] < array[h]) {
    return array[h];
  }
  if (l == h) {
    return array[h];
  }
  int mid;
  mid = (l + h) / 2;
  if ((mid + 1 <= h) && array[mid] > array[mid + 1]) {
    return array[mid];
  }
  if ((mid - 1 >= l) && array[mid - 1] > array[mid]) {
    return array[mid - 1];
  }
  if (array[mid] < array[h]) {
    return FindLargestNumber(array, l, mid - 1);
  } else {
    return FindLargestNumber(array, mid + 1, h);
  }
}
    
  
int main(int argc, char *argv[]) {
  int array[6] = {27,29,35,42,5,15};
  cout << FindLargestNumber(array, 0, 5) << endl;
  return 0;
}
