#include <iostream>
#include <cstring>
using namespace std;

#define N_CHARS 256

void ComputeTrans(char *pat, int m, int trans[][N_CHARS]) {
  int i, lps = 0, x;
  for (x = 0; x < N_CHARS; ++x) {
    trans[0][x] = 0;
  }
  trans[0][pat[0]] = 1;
  for (i = 1; i <= m; ++i) {
    for (x = 0; x < N_CHARS; ++x) {
      trans[i][x] = trans[lps][x];
    }
    trans[i][pat[i]] = i + 1;
    if (i < m) {
      lps = trans[lps][pat[i]];
    }
  }
}

void Search(char *pat, char *txt) {
  int m = strlen(pat);
  int n = strlen(txt);
  int trans[m+1][N_CHARS];
  ComputeTrans(pat, m, trans);
  int i, stat = 0;
  for (i = 0; i < n; ++i) {
    stat = trans[stat][txt[i]];
    if (stat == m) {
      cout << "pattern found at index " << i - m + 1 << endl;
    }
  }
}

int main() {
  char *txt = "ACACAGA FOR ACACAGA";
  char *pat = "ACA";
  Search(pat, txt);
  return 0;
}
