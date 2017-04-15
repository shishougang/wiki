#include <iostream>
#include <string>

using namespace std;

/* Transform S into T
 * For example, S = "aba", T = "^#a#b#a#$"
 * ^ and $ sings are sentinels appended to each end to avoid bouds checking 
 Run Status: Accepted!
 Program Runtime: 4 milli secs
 Program Runtime: 48 milli secs */
string preProcess(string s) {
  int n = s.length();
  if (n == 0)
    return "^$";
  string ret = "^";
  for (int i = 0; i < n; ++i)
    ret += "#" + s.substr(i, 1);
  ret += "#$";
  return ret;
}

string LongestPalindrome(string s) {
  string T = preProcess(s);
  int n = T.length();
  int *M = new int[n];
  int C = 0, R = 0, i_mirror;
  for (int i = 1; i < n - 1; ++i) {
    i_mirror = 2 * C - i; // C - (i -C)
    M[i] = (i < R)? min(M[i_mirror], R - i) : 0;
    //expand palindrome center at i
    while (T[i + 1 + M[i]] == T[i - 1 - M[i]])
      ++M[i];
    if (i + M[i] > R) {
      C = i;
      R = i + M[i];
    }
  }

  int maxLen = 0;
  int centerIndex = 0;
  for (int i = 1; i < n - 1; ++i) {
    if (M[i] > maxLen) {
      maxLen = M[i];
      centerIndex = i;
    }
  }
  delete[] M;
  return s.substr((centerIndex - 1 - maxLen) / 2, maxLen);
}

int main(int argc, char *argv[]) {
  string text;
  text = "babcbabcbaccba";
  cout << LongestPalindrome(text) << endl;

  text = "abaaba";
  cout << LongestPalindrome(text) << endl;

  text = "abababa";
  cout << LongestPalindrome(text) << endl;

  text = "abcbabcbabcba";
  cout << LongestPalindrome(text) << endl;
  return 0;
}
