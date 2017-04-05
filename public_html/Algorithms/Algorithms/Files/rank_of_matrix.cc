#include <iostream>

using namespace std;

#define R 3
#define C 3

void SwapRow(int mat[R][C], int row1, int row2,
          int col) {
  for (int i = 0; i < col; ++i) {
    int temp = mat[row1][i];
    mat[row1][i] = mat[row2][i];
    mat[row2][i] = temp;
  }
}

int RankOfMatrix(int mat[R][C]) {
  int rank = C;
  for (int row = 0; row < rank; ++row) {
    if (mat[row][row]) {
      for (int i = 0; i < R; ++i) {
        if (i != row) {
          double mult = (double)mat[i][row] /
                        mat[row][row];
          for (int j = 0; j < rank; ++j) {
            mat[i][j] -= mult * mat[row][j];
          }
        }
      }
    } else {
      bool reduce = true;
      for (int i = row + 1; i < R; ++i) {
        if (mat[i][row]) {
          SwapRow(mat, row, i, rank);
          reduce = false;
          break;
        }
      }
      if (reduce) {
        --rank;
        // copy the last column
        for (int i = 0; i < R; ++i) {
          mat[i][row] = mat[i][rank];
        }
      }
      --row;
    }
  }
  return rank;
}

int main() {
  int mat[][3] = {{10,   20,   10},
                  {-20,  -30,   10},
                  {30,   50,   0}};
  cout << "Rank of the matrix is : " <<
      RankOfMatrix(mat) << endl;
  return 0;
}
    
