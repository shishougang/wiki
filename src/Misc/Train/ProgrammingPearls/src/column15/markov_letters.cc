#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[]) {
  const int kMax = 50000;
  const int kK = 5;
  const int kPrintlen = 1000;
  char str[kMax];
  int c, n;
  n = 0;
  while ((c = getchar()) != EOF) {
    str[n++] = c;
  }
  str[n] = 0;
  char *p, *q, *next_p;
  p = str;
  int i, eq_sofar, j;
  for (i = 0; i < kK; ++i) {
    printf("%c", str[i]);
  }
  for (i = 0; i < kPrintlen; ++i) {
    eq_sofar = 0;
    for (q = str; q < str + n - kK + 1; ++q) {
      for (j = 0; j < kK && *(p + j) == *(q + j); ++j) {
      }
      if (j == kK) {
        eq_sofar++;
        if (rand() % eq_sofar == 0) {
          next_p = q;
        }
      }
    }
    c = *(next_p + kK);
    if (c == 0) {
      break;
    }
    putchar(c);
    p = next_p + 1;
  }
  return 0;
}
