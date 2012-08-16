#include <stdio.h>

#define MAXLEN 1001

int getline1(char s[], int lim)
{
  int c, i;
  for(i = 0; (i < lim -1) && ((c = getchar()) != EOF) && c != '\n'; i++){
    s[i] = c;
  }
  if(c == '\n' && i > 0){
    s[i] = c;
    i++;
  }
  s[i] = '\0';
  return i;
}
int main(int argc, char *argv[])
{
  char str[MAXLEN];
  int len;
  int i;

  while( (len = getline1(str, MAXLEN)) != 0){
    if(str[len - 1] == '\n')
      i = len - 2;
    else
      i = len - 1;
    for(; i >= 0; i--){
      if(str[i] == ' ' || str[i] == '\t')
        str[i] = '\0';
      else
        break;
    }
  
    if(i > 0)
      printf("%s\n", str);
  }
  

  return 0;
}
