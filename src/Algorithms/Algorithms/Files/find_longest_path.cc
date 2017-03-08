#include <iostream>
#include <cstring>
using namespace std;
#define n 3

int FindLongestFromACell(int i, int j, int mat[n][n], int dp[n][n]) {
  if (i < 0 || i >= n ||
      j < 0 || j >= n) {
    return 0;
  }
  if (dp[i][j] != -1) {
    return dp[i][j];
  }
  // Since all numbers are unique and in range from 1 to n*n,
  // there is atmost one possible direction from any cell
  if (i > 0 && (mat[i][j] + 1 == mat[i-1][j])) {
    return dp[i][j] = 1 + FindLongestFromACell(i-1, j, mat, dp);
  }
  if (i < n - 1 && (mat[i][j] + 1 == mat[i+1][j])) {
    return dp[i][j] = 1 + FindLongestFromACell(i+1, j, mat, dp);
  }
  if (j > 0 && (mat[i][j] + 1 == mat[i][j-1])) {
    return dp[i][j] = 1 + FindLongestFromACell(i, j-1, mat, dp);
  }
  if (j < n-1 && ((mat[i][j] + 1) == mat[i][j+1])) {
    return dp[i][j] = 1 + FindLongestFromACell(i, j+1, mat, dp);
  }
  return dp[i][j] = 1;
}

int FindLongestPath(int mat[n][n]) {
  int longest_path = 1;
  int dp[n][n];
  memset(dp, -1, sizeof(dp));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (dp[i][j] == -1) {
        FindLongestFromACell(i, j, mat, dp);
      }
      longest_path = max(longest_path, dp[i][j]);
    }
  }
  return longest_path;
}

int main() {
  int mat[n][n] = {{1, 2, 9},
                   {5, 3, 8},
                   {4, 6, 7}};
  cout << "Length of the longest path is "
       << FindLongestPath(mat) << endl;;
  return 0;
}
