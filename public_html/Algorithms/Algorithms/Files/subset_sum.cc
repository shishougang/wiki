#include <iostream>
#include <vector>

using namespace std;

bool IsSubsetSum(const vector<int> &vec, int sum) {
  int len = vec.size();
  int dp[len+1][sum+1];
  int i, j;
  for (i = 0; i <= len; ++i) {
    dp[i][0] = true;
  }
  for (i = 1; i <= sum; ++i) {
    dp[0][i] = false;
  }
  for (i = 1; i <= len; ++i) {
    for (j = 1; j <= sum; ++j) {
      dp[i][j] = dp[i-1][j];
      if (vec[i-1] <= j) {
        dp[i][j] = dp[i][j] || dp[i-1][j-vec[i-1]];
      }
    }
    if (dp[i][sum] == true) {
      return true;
    }
  }
  return false;
}

int main() {
  int set[] = {3, 5, 4, 12, 34, 2};
  int sum = 9;
  vector<int> vec(set, set + sizeof(set)/sizeof(set[0]));
  if (IsSubsetSum(vec, sum) == true) {
    cout << "Found a subset with given sum" << endl;
  } else {
    cout << "No subset with given sum" << endl;
  }
  return 0;
}
