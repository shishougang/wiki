#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

int FindMinInsertions(char *str, int l, int h) {
  if (l > h) {
    return INT_MAX;
  }
  if (l == h) {
    return 0;
  }
  if (l == h - 1) {
    return (str[l] == str[h])? 0 : l;
  }
  if (str[l] == str[h]) {
    return FindMinInsertions(str, l+1, h-1);
  } else {
    return (min(FindMinInsertions(str, l+1, h),
                FindMinInsertions(str, l, h-1)) + 1);
  }
}


int FindMinInsertions(char *str, int n) {
  int dp[n][n];
  int gap, i, j;
  memset(dp, 0, sizeof(dp));
  for (gap = 1; gap < n; ++gap) {
    for (i = 0, j = gap; j < n; ++i, ++j) {
      dp[i][j] = (str[i] == str[j]) ? dp[i+1][j-1] :
                 (min(dp[i][j-1], dp[i+1][j]) + 1);
    }
  }
  return dp[0][n-1];
}

int main() {
  char str[] = "geeks";
  cout << FindMinInsertions(str, 0, strlen(str)-1) << endl;
  cout << FindMinInsertions(str, strlen(str)) << endl;
  return 0;
}
