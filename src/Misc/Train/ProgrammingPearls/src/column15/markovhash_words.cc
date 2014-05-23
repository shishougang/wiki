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

char* SkipNword(char *p, int n) {
  for (; n > 0; p++) {
    if (*p == 0) {
      --n;
    }
  }
  return p;
}

#define NHASH 499979
#define MULT 31
int bin[NHASH];
int next[MAXWORDS];

unsigned int Hash(char *str) {
  unsigned int h = 0;
  char *p = str;
  for (int n = K; n > 0; p++) {
    h = MULT * h + (unsigned char)(*p);
    if (*p == 0) {
      --n;
    }
  }
  return h % NHASH;
}

void InitHash(char **word, int nword) {
  int i;
  for (i = 0; i < NHASH; ++i) {
    bin[i] = - 1;
  }
  for (i = 0; i < nword; ++i) {
    unsigned int h = Hash(word[i]);
    next[i] = bin[h];
    bin[h] = i;
  }
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
  InitHash(word, nword);
  for (i = 0; i < K; ++i) {
    printf("%s ", word[i]);
  }
  char *phrase = input_letters;
  int printlen = 100;
  char *p;
  for (; printlen > 0; --printlen) {
    i = 0;
    for (int j = bin[Hash(phrase)]; j >= 0; j = next[j]) {
      if (WordNcmp(word[j], phrase, K) == 0 && (rand() % (++i) == 0)) {
        p = word[j];
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

