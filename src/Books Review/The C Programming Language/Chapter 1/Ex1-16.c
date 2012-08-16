#include <stdio.h>

#define MAXLINE 20

int getline1(char s[], int lim);
void copy(char to[], char from[]);

int main(int argc, char *argv[])
{

  char line[MAXLINE];
  char temp[MAXLINE];
  char longest[MAXLINE];
  

  int len, premax, max, getmore;
  premax = max = getmore = 1;

  while((len = getline1(line, MAXLINE)) > 0){
    if(line[len -1] != '\n'){
      if(getmore == 0)
        copy(temp, line);
      premax += len;
      if(premax > max){
        max = premax;
        copy(longest, temp);
        longest[MAXLINE - 2] = '\n';
      }
      getmore = 1;
    }
    else{
      if(getmore == 1){
        if(max < (premax + len)){
          max = premax + len;
          copy(longest, temp);
          longest[MAXLINE - 2] = '\n';
        }
        getmore = 0;
      }
      else{
        if(max < len){
          max = len;
          copy(longest, line);
        }
      }
      premax = 0;
    }
  }

  if(max > 0){
    printf("%s", longest);
    printf("max = %d \n", max);
  }
    
  return 0;
}
int getline1(char s[], int lim)
{

  int i, c;
  for(i = 0; (i < lim - 1) && ((c = getchar()) != EOF) && (c != '\n'); i++){
    s[i] = c;
  }

  /* if(i > 0){
    s[i] = '\n';
    i++;
    }*/
  if( c == '\n' && i > 0){
    s[i] = c;
    i++;
  }
  else if(c == EOF && i > 0){
    s[i] = '\n';
    i++;
  }
  s[i] = '\0';

  return i;
}
      
void copy(char to[], char from[])
{
  int i = 0;
  while( (to[i] = from[i]) != '\0'){
    i++;
  }
}
