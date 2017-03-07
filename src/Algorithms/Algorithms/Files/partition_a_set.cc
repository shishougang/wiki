#include <iostream>
#include <vector>

using namespace std;

int FindMin(const vector<int> &vec) {
  int sum = 0;
  int len = vec.size();
  int i, j;
  for (i = 0; i < len; ++i) {
    sum += vec[i];
  }
  bool dp[len+1][sum+1];
  for (i = 0; i <= len; ++i) {
    dp[i][0] = true;
  }
  for (i = 0; i <= sum; ++i) {
    dp[0][i] = false;
  }
  for (i = 1; i <= len; ++i) {
    for (j = 1; j <= sum; ++j) {
      dp[i][j] = dp[i-1][j];
      if (vec[i-1] <= j) {
        dp[i][j] |= dp[i-1][j-vec[i-1]];
      }
    }
  }
  int diff;
  for (i = sum / 2; i >= 0; --i) {
    if (dp[len][i] == true) {
      diff = sum - 2 * i;
      break;
    }
  }
  return diff;
}

int main() {
  int arr[] = {3, 1, 4, 2, 2, 1};
  vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
  cout << "The minimum difference between 2 sets is "
       << FindMin(vec) << endl;;
  return 0;
}
    
