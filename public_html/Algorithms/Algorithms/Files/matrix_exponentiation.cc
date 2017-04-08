#include <iostream>

using namespace std;

#define N 3
void Multiply(int a[N][N], int b[N][N]) {
  int mul[N][N];
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      mul[i][j] = 0;
      for (int k = 0; k < N; ++k) {
        mul[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      a[i][j] = mul[i][j];
    }
  }
}

int Power(int F[3][3], int n) {
  if (n == 1) {
    return F[0][0] + F[0][1];
  }
  Power(F, n / 2);
  Multiply(F, F);
  if (n % 2 != 0) {
    int M[3][3] = {{1,1,1}, {1,0,0}, {0,1,0}};
    Multiply(F, M);
  }
  // F(0) = 0, F(1) = 1, F(2) = 1
  return F[0][0] + F[0][1];
}

// f(n) = f(n-1) + f(n-2) + f(n-3), n>=3
// Base Cases :
// f(0) = 0, f(1) = 1, f(2) = 1
int FindNth(int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1 || n == 2) {
    return 1;
  }
  int F[3][3] = {{1,1,1}, {1,0,0}, {0,1,0}} ;
  return Power(F, n-2);
}

int main() {
  int n = 5;
  cout << "F(5) is " << FindNth(n);
  return 0;
}
