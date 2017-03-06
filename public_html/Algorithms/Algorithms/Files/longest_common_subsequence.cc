#include <string>
#include <iostream>
using namespace std;

int LCS(const string& x1, const string& x2) {
  int m = x1.size();
  int n = x2.size();
  int L[m+1][n+1];
  int i, j;

  for (i = 0; i <= m; ++i) {
    for (j = 0; j <= n; ++j) {
      if (i == 0 || j == 0) {
        L[i][j] = 0;
      } else {
        if (x1[i] == x2[j]) {
          L[i][j] = L[i-1][j-1] + 1;
        } else {
          L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
      }
    }
  }
  return L[m][n];
}

int main() {
  string x1 = "AGGTAB";
  string x2 = "GXTXAYB";
  cout << "Length of LCS is " << LCS(x1, x2) << endl;
  return 0;
} 
 
