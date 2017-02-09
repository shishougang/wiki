#include <iostream>  // NOLINT
using std::cout;
using std::endl;

bool CheckEqualIndex(int *array, int l, int h) {
  while (l <= h) {
    int mid = (l + h) / 2;
    if (array[mid] > (mid + 1)) {
      h = mid - 1;
    } else if (array[mid] < (mid + 1)) {
      l = mid + 1;
    } else {
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  int array[5] = {-10,-3,3,5,7};
  if (CheckEqualIndex(array, 0, 4)) {
    cout << "find" << endl;
  } else {
    cout << "not find" << endl;
  }
  int array2[6] = {2,3,4,5,6,7};
  if (CheckEqualIndex(array2, 0, 5)) {
    cout << "find" << endl;
  } else {
    cout << "not find" << endl;
  }
  
  return 0;
}

    
  
