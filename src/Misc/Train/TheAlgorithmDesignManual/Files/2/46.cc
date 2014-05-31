#include <cstdio>
#include <algorithm>
using std::max;
#include <limits>
using std::numeric_limits;

/* Drop Marbles
   n: num of marbles
   r: num of floors
   drop_qeq: the drop sequence
   marble_drop: minimum number of trails needed to find the critical floor in
   worst case
   marble_drop[n][r] = 1 + min{max(marble_drop[n-1][x-1], marble[n][r-x]) :
   x in {1,2,...,r}}
*/
int DropMarbles(int n, int r, int **drop_seq) {
  int marble_drop[n+1][r+1];
  int i, j;
  for (j = 0; j <= r; ++j) {
    marble_drop[1][j] = j;
  }
  for (i = 0; i <= n; ++i) {
    marble_drop[i][1] = 1;
    marble_drop[i][0] = 0;
  }
  int min_sofar;
  for (i = 2; i <= n; ++i) {
    for (j = 2; j <= r; ++j) {
      marble_drop[i][j] = numeric_limits<int>::max();
      for (int x = 1; x <= j; ++x) {
        min_sofar = 1 + max(marble_drop[i-1][x-1], marble_drop[i][j-x]);
        if (min_sofar < marble_drop[i][j]) {
          marble_drop[i][j] = min_sofar;
          drop_seq[i][j] = x;
        }
      }
    }
  }
  return marble_drop[n][r];
}

int main(int argc, char *argv[]) {
  int n = 2, r = 100;
  int **drop_seq;
  drop_seq = new int*[n+1];
  for (int i = 0; i <= n; ++i) {
    drop_seq[i] = new int[r+1];
  }
  int res;
  res = DropMarbles(n, r, drop_seq);
  printf("\nMinimum number of trials in worst case with %d eggs and "
          "%d floors is %d \n", n, r, res);
  printf("one of the worst case: \n");
  int total_floor = r;
  int down_floor = 0;
  for (int i = 0; i < res; ++i) {
    total_floor -= down_floor;
    down_floor = drop_seq[n][total_floor];
    printf("%d-->", down_floor + r - total_floor);
  }
  return 0;
}
