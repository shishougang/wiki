#include <cstdio>

void Reverse(char *begin, char *end) {
  char temp;
  while (begin < end) {
    temp = *begin;
    *begin = *end;
    *end = temp;
    begin++;
    end--;
  }
}

void ReverseWords(char *str) {
  char *word_begin;
  word_begin = NULL;
  char *p;
  p = str;
  while (*p != '\0') {
    if (word_begin == NULL && *p != ' ') {
      word_begin = p;
    }
    if (word_begin != NULL && (*(p+1) == ' ' || *(p+1) == '\0')) {
      Reverse(word_begin, p);
      word_begin = NULL;
    }
    ++p;
  }
  Reverse(str, p - 1);
}

int main(int argc, char *argv[])
{
  char str[] = "My name is Chris";
  printf("%s\n", str);
  ReverseWords(str);
  printf("%s\n", str);
  return 0;
}

      
