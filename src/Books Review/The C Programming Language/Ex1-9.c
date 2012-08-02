#include <stdio.h>
int main(void)
{
  int c;
  int flag;
  while((c = getchar()) != EOF){
    if(c != ' ')
      flag = 0;
    if(flag == 0)
      printf("%c", c);
    if(c == ' ')
      flag = 1;
  }
  return 0;
}
