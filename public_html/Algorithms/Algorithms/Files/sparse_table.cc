#include <iostream>
#include <cmath>

using namespace std;

#define MAX 500

int lookup[MAX][MAX];

struct Query {
  int l, r;
};

void PreProcess(int *arr, int n) {
  for (int i = 0; i < n; ++i) {
    lookup[i][0] = i;
  }
  for (int j = 1; (1<<j) <= n; ++j) {
    for (int i = 0; (i+(1<<j)-1) < n; ++i) {
      // i, j -> i, i+2^j
      // i, j-1-> i, i+2^(j-1)  i+2^(j-1), j -> i+2^(j-1), i+2^j
      if (arr[lookup[i][j-1]] < arr[lookup[i+(1<<(j-1))][j-1]]) {
        lookup[i][j] = lookup[i][j-1];
      } else {
        lookup[i][j] = lookup[i+(1<<(j-1))][j-1];
      }
    }
  }
}

int Query(int *arr, int l, int r) {
  int j = (int)log2(r-l+1);
  if (arr[lookup[l][j]] <= arr[lookup[r-(int)pow(2,j)+1][j]]) {
    return arr[lookup[l][j]];
  } else {
    return arr[lookup[r-(int)pow(2,j)+1][j]];
  }
}

void RMQ(int *arr, int n, struct Query *q, int m) {
  PreProcess(arr, n);
  for (int i = 0; i < m; ++i) {
    int l = q[i].l, r = q[i].r;
    cout << "Minimum of [" << l << ", "
         << r << "] is "  << Query(arr, l, r) << endl;
  }
}

int main() {
  int a[] = {7, 2, 3, 0, 5, 10, 3, 12, 18};
  int n = sizeof(a)/sizeof(a[0]);
  struct Query q[] = {{0, 4}, {4, 7}, {7, 8}};
  int m = sizeof(q)/sizeof(q[0]);
  RMQ(a, n, q, m);
  return 0;
}
