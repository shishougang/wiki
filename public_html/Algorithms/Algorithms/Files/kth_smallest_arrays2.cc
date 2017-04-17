#include <iostream>

using namespace std;

int KthSmallest(int *a, int n, int *b, int m, int k) {
  if (k > (n + m)) {
    return -1;
  }
  int len_a = n, len_b = m;
  int l_a = 0, l_b = 0, step;
  while (k > 2) {
    step = (k - 1) / 2;
    if (step >= n) {
      l_b += step;
      m -= step;
    } else if (step >= m || a[step+l_a] <= b[step+l_b]) {
      l_a += step;
      n -= step;
    } else {
      l_b += step;
      m -= step;
    }
    k -= step;
    cout << l_a << " " << l_b << endl;
  }
  
  if (l_a == len_a) {
    return b[l_b+1];
  }
  if (l_b == len_b) {
    return a[l_a+1];
  }
  return max(a[l_a], b[l_b]);
}


int main() {
  //int a[] = {9, 12, 15, 900};
  //int b[] = {8, 10, 20};
  int a[] = {1, 2 ,3};
  int b[] = {8, 10, 20};
  int n = sizeof(a) / sizeof(a[0]);
  int m = sizeof(b) / sizeof(b[0]);
  int k = 5;
  cout << KthSmallest(a, n, b, m, k) << endl;
  return 0;
}
