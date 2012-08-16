#include <stdio.h>
#define MIN_PRINT 81
int getline1(char s[], int lim)
{
  int c;
  int i;
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

  int len;
  char s[MIN_PRINT];
  int c;
  while( (len = getline1(s, MIN_PRINT)) != 0){
    if( (len == MIN_PRINT - 1) && s[MIN_PRINT-2] != '\n'){
      printf("%s", s);
      while( (c = getchar()) != EOF && c != '\n'){
        putchar(c);
      }
      putchar('\n');
      if(c == EOF)
        return 0;
    }
  }
        
  return 0;
}
