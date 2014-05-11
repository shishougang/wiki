#include <iostream> // NOLINT
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;

struct MatrixElem {
  MatrixElem(int i_data, int i_row, int i_col) {
    data = i_data;
    row = i_row;
    col = i_col;
  }
  int data;
  int row;
  int col;
};

bool MatrixElemComp(const MatrixElem &lhs, const MatrixElem &rhs) {
  if (lhs.col == rhs.col) {
    return lhs.row < rhs.row;
  } else {
    return lhs.col < rhs.col;
  }
}

void TransposeMatrix(const vector<vector<int> > &matrix,
                     vector<vector<int> > *trans_matrix) {
  vector<MatrixElem> matrix_vector;
  int n_row;
  int n_col;
  n_row = matrix.size();
  if (n_row < 1) {
    return;
  }
  n_col = matrix[0].size();

  for (int row = 0; row < n_row; ++row) {
    for (int col = 0; col < n_col; ++col) {
      MatrixElem elem = MatrixElem(matrix[row][col], row, col);
      matrix_vector.push_back(elem);
    }
  }

  sort(matrix_vector.begin(), matrix_vector.end(), MatrixElemComp);

  trans_matrix->resize(n_row);
  for (int row = 0;  row < n_row; ++row) {
    (trans_matrix->at(row)).resize(n_col);
  }

  for (int i = 0; i < matrix_vector.size(); ++i) {
    (*trans_matrix)[i / n_row][i % n_row] = matrix_vector[i].data;
  }
}

void PrintMatrix(const vector<vector<int> > &matrix) {
  for (int row = 0; row < matrix.size(); ++row) {
    for (int col = 0; col < matrix[row].size(); ++col) {
      cout << matrix[row][col] << " ";
    }
    cout << endl;
  }
}

int main(int argc, char *argv[]) {
  vector<vector<int> > matrix;
  vector<vector<int> > trans_matrix;
  vector<int> temp;
  for (int row = 0; row < 10; ++row) {
    for (int col = 0; col < 10; ++col) {
      temp.push_back(row*10 + col);
    }
    matrix.push_back(temp);
    temp.clear();
  }
  PrintMatrix(matrix);
  TransposeMatrix(matrix, &trans_matrix);
  cout << "transpose:" << endl;
  PrintMatrix(trans_matrix);
  return 0;
}

