#include <stdio.h>
int main(void)
{
  int nblanks, ntabs, nnewlines;
  int c;
  int done = 0;

  nblanks = 0;
  ntabs = 0;
  nnewlines = 0;

  while(done == 0){
    c = getchar();
    if(c == ' ')
      nblanks++;
    else if(c == '\t')
      ntabs++;
    else if(c == '\n')
      nnewlines++;
    else if(c == EOF)
      done = 1;
  }

  printf("Blanks: %d\n Tabs: %d\n Newlines: %d\n", nblanks, ntabs, nnewlines);
  return 0;
}
