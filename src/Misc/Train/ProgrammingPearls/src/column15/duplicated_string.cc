#include <cstdlib>
#include <cstdio>
#include <cstring>

int CmpPstr(const void *a, const void *b) {
  const char **p = (const char **)a;
  const char **q = (const char **)b;
  return strcmp(*p, *q);
}

int ComLen(char *p, char *q) {
  int i = 0;
  while (*p && (*p == *q)) {
    ++i;
    ++p;
    ++q;
  }
  return i;
}

#define kMaxN 500000
#define kM 1
char str[kMaxN];
char *pstr[kMaxN];
int main(int argc, char *argv[]) {
  int ch;
  int n = 0;
  while ((ch = getchar()) != EOF) {
    str[n] = ch;
    pstr[n] = &str[n];
    ++n;
  }
  str[n] = 0;
  qsort(pstr, n, sizeof(char *), CmpPstr);
  int maxlen = 0;
  int maxindex = 0;
  for (int i = 0; i < n - kM; ++i) {
    if (ComLen(pstr[i], pstr[i + kM]) > maxlen) {
      maxlen = ComLen(pstr[i], pstr[i + kM]);
      maxindex = i;
    }
  }
  printf("%.*s\n", maxlen, pstr[maxindex]);
  return 0;
}
