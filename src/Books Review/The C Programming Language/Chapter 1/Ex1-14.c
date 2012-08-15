#include <stdio.h>

#define MAX_CHAR 256
int main(int argc, char *argv[])
{
  int c;
  int freqchar[MAX_CHAR + 1];
  int i, j;
  int max_freq;

  for(i = 0; i <= MAX_CHAR; i++)
    freqchar[i] = 0;
  max_freq = 0;

  while( (c = getchar()) != EOF){
    if(c < MAX_CHAR){
      freqchar[c]++;
      max_freq = (freqchar[c] > max_freq) ? freqchar[c] : max_freq;
    }
    else{
      freqchar[MAX_CHAR]++;
      if(freqchar[MAX_CHAR] > max_freq)
        max_freq = freqchar[MAX_CHAR];
    }
  }

  for(i = max_freq; i > 0; i--){
    printf("%5d |", i);
    for(j = 0; j <= MAX_CHAR; j++){
      if(freqchar[j] >= i)
        printf("*");
      else if(freqchar[j] > 0)
        printf(" ");
    }
    printf("\n");
  }
  printf("      +");
  for(i = 0; i <= MAX_CHAR; i++){
    if(freqchar[i] > 0)
      printf("-");
  }
  printf("\n        ");

  for(i = 0; i < MAX_CHAR; i++){
    if(freqchar[i] > 0){
      printf("%d", i/100);
    }
  }
  printf("\n        ");
  for(i = 0; i < MAX_CHAR; i++){
    if(freqchar[i] > 0){
      printf("%d", (i - (i/100) * 100) / 10);
    }
  }
  printf("\n        ");
  for(i = 0; i < MAX_CHAR; i++){
    if(freqchar[i] > 0){
      printf("%d", i % 10);
    }
  }

  if(freqchar[MAX_CHAR] > 0)
    printf(">%d\n", MAX_CHAR);
  printf("\n");
      
  
  return 0;
}

