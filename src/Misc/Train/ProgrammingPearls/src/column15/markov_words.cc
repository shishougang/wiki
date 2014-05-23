#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXINPUT 4000000
#define MAXWORDS 800000
#define K 2
char input_letters[MAXINPUT];
char *word[MAXWORDS];

int WordNcmp(const char *p, const char *q, int n) {
  while (*p == *q) {
    if (*p == 0 && --n == 0) {
      return 0;
    }
    ++p;
    ++q;
  }
  return *p - *q;
}


int SortCmp(const void *a, const void *b) {
  const char **p = (const char**)(a);
  const char **q = (const char**)(b);
  return WordNcmp(*p, *q, K);
}

char* SkipNword(char *p, int n) {
  for (; n > 0; p++) {
    if (*p == 0) {
      --n;
    }
  }
  return p;
}

int FindPhrase(char **word, int n, char *phrase) {
  int l = -1;
  int u = n;
  int m;
  while (l + 1 != u) {
    m = (l + u) / 2;
    if (WordNcmp(word[m], phrase, K) < 0) {
      l = m;
    } else {
      u = m;
    }
  }
  return u;
}

int main(int argc, char *argv[]) {
  int nword = 0;
  word[0] = input_letters;
  while (scanf("%s", word[nword]) != EOF) {
    word[nword + 1] = word[nword] + strlen(word[nword]) + 1;
    nword++;
    if (nword == MAXWORDS) {
      break;
    }
  }
  int i;
  for (i = 0; i < K; ++i) {
    word[nword][i] = 0;
  }
  for (i = 0; i < K; ++i) {
    printf("%s ", word[i]);
  }
  qsort(word, nword, sizeof(word[0]), SortCmp);
  char *phrase = input_letters;
  int printlen = 100;
  int find_index;
  char *p;
  for (; printlen > 0; --printlen) {
    int find_index = FindPhrase(word, nword, phrase);
    for (i = 0; WordNcmp(phrase, word[find_index + i], K) == 0; ++i) {
      if ((rand() % (i + 1)) == 0) {
        p = word[find_index + i];
      }
    }
    phrase = SkipNword(p, 1);
    if (strlen(SkipNword(phrase, K - 1)) == 0) {
      break;
    }
    printf("%s ", SkipNword(phrase, K - 1));
  }
  printf("\n");
  return 0;
}

