#include <iostream>  // NOLINT
using std::cout;
using std::endl;
#include <algorithm>
using std::swap;

void BubbleSort(int *array, int left, int right) {
  int bound = right;
  while (1) {
    int tmp = 0;
    for (int i = left; i <= right; ++i) {
      if (array[i] > array[i + 1]) {
        swap(array[i], array[i + 1]);
        tmp = i;
      }
    }
    if (tmp == 0) {
      break;
    }
    bound = tmp;
  }
}
  
int FindMedian(int *array, int left, int right) {
  const int kGroupSize = 5;
  int size = right - left + 1;
  if (size <= kGroupSize) {
    BubbleSort(array, left, right);
    return array[(size - 1) / 2 + 1];
  }
  int num_group = (size - kGroupSize + 1) / kGroupSize;
  for (int i = 0; i < num_group; ++i) {
    int sub_left = left + kGroupSize * i;
    int sub_right = sub_left + kGroupSize - 1;
    if (sub_right > right) {
      sub_right = right;
    }
    BubbleSort(array, sub_left, sub_right);
    swap(array[left + i], array[(right + left - 1) / 2 + 1]);
  }
  return FindMedian(array, left, left + num_group - 1);
}

int main(int argc, char *argv[])
{
  const int kN = 11;
  int array[kN];
  for (int i = 0; i < kN; ++i) {
    array[i] = i;
  }
  int mid_value = FindMedian(array, 0, kN - 1);
  cout << mid_value << endl;
  return 0;
}

