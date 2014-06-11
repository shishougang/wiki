#include <iostream>  // NOLINT
using std::cout;
using std::endl;

bool FindElement(int **array, int x, int n, int m, int *pos_x, int *pos_y) {
  int row = 0, col = m - 1;
  while (row < n && col >= 0) {
    if (array[row][col] == x) {
      *pos_x = row;
      *pos_y = col;
      return true;
    } else if (array[row][col] > x) {
      col--;
    } else {
      row++;
    }
  }
  return true;
}
