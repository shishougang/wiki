#include <iostream>
#include <string>

using namespace std;

int CountParenth(const string& symb, const string& oper) {
  int n = symb.size();
  int F[n][n], T[n][n];
  for (int i = 0; i < n; ++i) {
    T[i][i] = (symb[i] == 'T') ? 1 : 0;
    F[i][i] = (symb[i] == 'F') ? 1 : 0;
  }
  for (int gap = 1; gap < n; ++gap) {
    for (int i = 0, j = gap; j < n; ++i, ++j) {
      T[i][j] = F[i][j] = 0;
      for (int k = i; k < j; ++k) {
        int total_ik = T[i][k] + F[i][k];
        int total_kj = T[k+1][j] + F[k+1][j];
        if (oper[k] == '&') {
          T[i][j] += T[i][k] * T[k+1][j];
          F[i][j] += (total_ik * total_kj - T[i][k] * T[k+1][j]);
        } else if (oper[k] == '|') {
          F[i][j] += F[i][k] * F[k+1][j];
          T[i][j] += (total_ik * total_kj - F[i][k] * F[k+1][j]);
        } else if (oper[k] == '^') {
          T[i][j] += F[i][k]*T[k+1][j] + T[i][k]*F[k+1][j];
          F[i][j] += T[i][k]*T[k+1][j] + F[i][k]*F[k+1][j];
        }
      }
    }
  }
  return T[0][n-1];
}

int main() {
  string symbols = "TTFT";
  string operators = "|&^";
  // There are 4 ways
  // ((T|T)&(F^T)), (T|(T&(F^T))), (((T|T)&F)^T) and (T|((T&F)^T))
  cout << CountParenth(symbols, operators) << endl;
  return 0;
}
