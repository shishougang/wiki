#include <iostream>
#include <string>

using namespace std;
#define D 256

void Search(const string& txt, const string& pat, int q) {
  int n = txt.size();
  int m = pat.size();
  int i, j;
  int p = 0; // hash value for pattern
  int t = 0; // hash value for txt
  int h = 1;
  // The value of h would be "pow(d, M-1)%q"
  for (i = 0; i < m-1; ++i) {
    h = (h * D) % q;
  }
  for (i = 0; i < m; ++i) {
    p = (D * p + pat[i]) % q;
    t = (D * t + txt[i]) % q;
  }
  for (i = 0; i <= n - m; ++i) {
    // Check the hash values of current window of text
    // and pattern.
    if (p == t) {
      for (j = 0; j < m; ++j) {
        if (txt[i+j] != pat[j]) {
          break;
        }
      }
      if (j == m) {
        cout << "Pattern found at index " << i << endl;
      }
    }
    if (i < n - m) {
      t = (D * (t - txt[i] * h) + txt[i+m]) % q;
      // might get negative value of t, converting it
      // to positive
      if (t < 0) {
        t += q;
      }
    }
  }
}

int main() {
  string txt = "GEEKS FOR GEEKS";
  string pat = "GEEK";
  int q = 101; // A prime number
  Search(txt, pat, q);
  return 0;
}
