#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;


int g_block;

struct Query {
  int l, r;
};

bool Compare(Query x, Query y) {
  if (x.l / g_block != y.l / g_block) {
    return x.l / g_block < y.l / g_block;
  }
  return x.r < y.r;
}

void QueryResults(int *a, int n, Query *q, int m) {
  g_block = sqrt(n);
  sort(q, q + m, Compare);
  int curr_l = 0, curr_r = 0;
  int curr_sum = 0;
  for (int i = 0; i < m; ++i) {
    int l = q[i].l;
    int r = q[i].r;
    while (curr_l < l) {
      curr_sum -= a[curr_l++];
    }
    while (curr_l > l) {
      curr_sum += a[curr_l-1];
      --curr_l;
    }
    while (curr_r <= r) {
      curr_sum += a[curr_r++];
    }
    while (curr_r > r + 1) {
      curr_sum -= a[curr_r-1];
      --curr_r;
    }
    cout << "Sum of [" << l << ", " << r
         << "] is "  << curr_sum << endl;
  }
}

int main() {
  int a[] = {1, 1, 2, 1, 3, 4, 5, 2, 8};
  int n = sizeof(a)/sizeof(a[0]);
  Query q[] = {{0, 4}, {1, 3}, {2, 4}};
  int m = sizeof(q)/sizeof(q[0]);
  QueryResults(a, n, q, m);
  return 0;
}
