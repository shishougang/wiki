#include <iostream>  // NOLINT
using std::cout;
using std::endl;

int CountZero(int **array, int n) {
  int row = n - 1, col = n - 1;
  int count = 0;
  while (row >=0 && col >= 0) {
    if (array[row][col] == 0) {
      count++;
      row--;
    } else if(array[row][col] > 0) {
      col--;
    } else {
      row--;
    }
  }
  return count;
}

int main(int argc, char *argv[]) {
  int array[2][2];
  array[0][0] = -5;
  array[0][1] = 0;
  array[1][0] = -6;
  array[1][1] = -1;
  cout << CountZero(array, 2) << endl;
  return 0;
}
