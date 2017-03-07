#include <iostream>

using namespace std;

int CountCover(int dist) {
  int dp[dist+1];
  dp[0] = 1;
  dp[1] = 1;
  dp[2] = 2;
  for (int i = 3; i <= dist; ++i) {
    dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
  }
  return dp[dist];
}

int main() {
  cout << CountCover(3) << endl;
  return 0;
}
