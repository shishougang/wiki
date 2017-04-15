#include <iostream>
#include <cstring>
using namespace std;

#define N_CHARS 256

int GetNextState(char *pat, int m, int state, int x) {
  if (state < m && x == pat[state]) {
    return state + 1;
  }
  int next_state, i;
  for (next_state = state; next_state > 0; --next_state) {
    if (pat[next_state-1] == x) {
      for (i = 0; i < next_state - 1; ++i) {
        if (pat[i] != pat[state-next_state+1+i]) {
          break;
        }
      }
      if (i == next_state - 1) {
        return next_state;
      }
    }
  }
  return 0;
}

void ComputeTrans(char *pat, int m, int trans[][N_CHARS]) {
  int state, x;
  for (state = 0; state <= m; ++state) {
    for (x = 0; x < N_CHARS; ++x) {
      trans[state][x] = GetNextState(pat, m, state, x);
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
