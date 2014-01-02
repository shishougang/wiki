
#define NDEBUG
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int val = 0;

static void field_abort(int sig)
{
}

int main()
{
  printf("%d \n", EXIT_FAILURE);
}

  
