#include <iostream>
#include <string>

using namespace std;

void GetZ(const string& str, int *z) {
  int len = str.size();
  int k, L, R;
  L = R = 0;
  for (int i = 1; i < len; ++i) {
    if (i > R) {
      L = R = i;
      // if i>R nothing matches so we will calculate Z[i] using naive way.
      while (R < len && str[R-L] == str[R]) {
        ++R;
      }
      z[i] = R - L;
      --R;
    } else {
      k = i - L;
      // if Z[k] is less than remaining interval
      // then Z[i] will be equal to Z[k].
      // For example, str = "ababab", i = 3, R = 5
      // and L = 2
      if (z[k] < R - i + 1) {
        z[i] = z[k];
      } else {
        // For example str = "aaaaaa" and i = 2, R is 5,
        // L is 0
        // else start from R and check manually
        L = i;
        while (R < len && str[R-L] == str[R]) {
          ++R;
        }
        z[i] = R - L;
        --R;
      }
    }
  }
}

void Search(const string& text, const string& pattern) {
  string concat = pattern + "$" + text;
  int len = concat.size();
  int z[len];
  GetZ(concat, z);
  for (int i = pattern.size(); i < len; ++i) {
    if (z[i] == pattern.size()) {
      cout << "Pattern found at index "
           << i - pattern.size() - 1 << endl;
    }
  }
}

int main() {
  string text = "GEEKS FOR GEEKS";
  string pattern = "GEEK";
  Search(text, pattern);
  return 0;
}
