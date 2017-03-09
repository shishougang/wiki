#include <iostream>

using namespace std;

int KnapSackSimple(int W, int *wt, int *val, int n) {
  if (n == 0 || W == 0) {
    return 0;
  }
  if (wt[n-1] > W) {
    return KnapSackSimple(W, wt, val, n-1);
  } else {
    return max(val[n-1] + KnapSackSimple(W-wt[n-1], wt, val, n-1),
               KnapSackSimple(W, wt, val, n-1));
  }
}

int KnapSack(int W, int *wt, int *val, int n) {
  int dp[n+1][W+1];
  int i, j;
  for (i = 0; i <= W; ++i) {
    dp[0][i] = 0;
  }
  for (i = 0; i <= n; ++i) {
    dp[i][0] = 0;
  }
  for (i = 1; i <= n; ++i) {
    for (j = 1; j <= W; ++j) {
      dp[i][j] = dp[i-1][j];
      if (j >= wt[i-1]) {
        dp[i][j] = max(dp[i][j], val[i-1] + dp[i-1][j-wt[i-1]]);
      }
    }
  }
  return dp[n][W];
}

int main() {
  int val[] = {60, 100, 120};
  int wt[] = {10, 20, 30};
  int  W = 50;
  int n = sizeof(val)/sizeof(val[0]);
  cout << KnapSackSimple(W, wt, val, n) << endl;
  cout << KnapSack(W, wt, val, n) << endl;
  return 0;
}

