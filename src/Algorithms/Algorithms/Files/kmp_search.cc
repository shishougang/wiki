#include <iostream>
#include <string>

using namespace std;

void ComputeLPS(const string& pat, int *lps) {
  // length of the previous longest prefix suffix
  int len = 0;
  lps[0] = 0;
  int i = 1;
  int m = pat.size();
  while (i < m) {
    if (pat[i] == pat[len]) {
      ++len;
      lps[i] = len;
      ++i;
    } else {
      if (len != 0) {
        len = lps[len-1];
      } else {
        lps[i] = 0;
        ++i;
      }
    }
  }
}

void KMPSearch(const string& txt, const string& pat) {
  int m = pat.size();
  int n = txt.size();
  int lps[m];
  ComputeLPS(pat, lps);
  int i = 0;
  int j = 0;
  while (i < n) {
    if (txt[i] == pat[j]) {
      ++i;
      ++j;
    }
    if (j == m) {
      cout << "Found pattern at index " << i - j << endl;
      j = lps[j-1];
    } else if (i < n && txt[i] != pat[j]) {
      if (j != 0 ) {
        j = lps[j-1];
      } else {
        ++i;
      }
    }
  }
}

int main() {
  string txt = "ABABDABACDABABCABAB";
  string pat = "ABABCABAB";
  KMPSearch(txt, pat);
  return 0;
}
