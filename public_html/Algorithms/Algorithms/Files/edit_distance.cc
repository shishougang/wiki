#include <iostream>
#include <string>
using namespace std;

int EditDistance(const string& str1, const string& str2) {
  int m = str1.size();
  int n = str2.size();
  int dis[m+1][n+1];
  for (int i = 0; i <= m; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (i == 0) {
        dis[i][j] = j;
      } else if (j == 0) {
        dis[i][j] = j;
      } else if (str1[i - 1] == str2[j - 1]) {
        dis[i][j] = dis[i - 1][j - 1];
      } else {
        dis[i][j] = 1 + min(min (dis[i][j - 1], // insert
                                 dis[i - 1][j]),  // remove
                            dis[i - 1][j - 1]); // replace
      }
    }
  }
  return dis[m][n];
}

int main() {
  string str1 = "sunday";
  string str2 = "saturday";
  cout << EditDistance(str1, str2) << endl;
  return 0;
}
