#include <iostream>

using namespace std;

int KthSmallest(int *a, int n, int *b, int m, int k) {
  cout << n << " " << m << " " << k <<  endl;
  if (n == 0) {
    return (m >= k ? b[k-1] : -1);
  }
  if (m == 0) {
    return (n >= k ? a[k-1] : -1);
  }
  int med_a = n / 2;
  int med_b = m / 2;
  if ((med_a + med_b + 2) <= k) {
    if (a[med_a] > b[med_b]) {
      return KthSmallest(a, n, b+med_b+1, m-med_b-1, k-med_b-1);
    } else {
      return KthSmallest(a+med_a+1, n-med_a-1, b, m, k-med_a-1);
    }
  } else {
    cout << a[med_a] << " " << b[med_b] << endl;
    if (a[med_a] > b[med_b]) {
      return KthSmallest(a, med_a, b, m, k);
    } else {
      return KthSmallest(a, n, b, med_b, k);
    }
  }
}

int main() {
  int a[] = {9, 12, 15, 900};
  int b[] = {8, 10, 20};
  int n = sizeof(a) / sizeof(a[0]);
  int m = sizeof(b) / sizeof(b[0]);
  int k = 4;
  cout << KthSmallest(a, n, b, m, k) << endl;
  return 0;
}

