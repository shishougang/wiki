#include <iostream>

using namespace std;

float MedianOf2(int a, int b) {
  return (a + b) / 2.0;
}

float MedianOf3(int a, int b, int c) {
  return a + b + c -
      max(a, max(b, c)) -
      min(a, min(b, c));
}

float MedianOf4(int a, int b, int c, int d) {
  int max_num = max(a, max(b, max(c, d)));
  int min_num = min(a, min(b, min(c, d)));
  return (a + b + c + d - max_num - min_num) / 2.0;
}

float MedianSingle(int *arr, int n) {
  if (n == 0) {
    return -1;
  } else if (n % 2 == 0) {
    return (arr[n/2-1] + arr[n/2]) / 2.0;
  }
  return arr[n/2];
}

float FindMedianUtil(int *a, int n, int *b, int m) {
  if (n == 0) {
    return MedianSingle(b, m);
  }
  if (n == 1) {
    // case 1
    if (m == 1) {
      return MedianOf2(a[0], b[0]);
    }
    // case 2 odd
    if (m & 1) {
      return MedianOf2(b[m/2], MedianOf3(a[0], b[m/2-1], b[m/2+1]));
    }
    // case 3 even
    return MedianOf3(b[m/2], b[m/2-1], a[0]);
  } else if (n == 2) {
    // case 4
    if (m == 2) {
      return MedianOf4(a[0], a[1], b[0], b[1]);
    }
    // case 5 odd
    if (m & 1) {
      return MedianOf3(b[m/2],
                       max(a[0], b[m/2-1]),
                       min(a[1], b[m/2+1]));
    }
    // case 6 even
    return MedianOf4(b[m/2],
                     b[m/2-1],
                     max(a[0], b[m/2-2]),
                     min(a[1], b[m/2+1]));
  }
  int med_a = (n - 1) / 2;
  int med_b = (m - 1) / 2;
  // a[med_a, .], b[., med_b], subtract same value 
  if (a[med_a] <= b[med_b]) {
    return FindMedianUtil(a+med_a, n - med_a , b, m - med_a);
  }
  // a[.,med_a], b[med_b, .], subtract same value 
  return FindMedianUtil(a, med_a+1, b+(n-(med_a+1)), m-(n-(med_a+1)));
}

float FindMedian(int *a, int n, int *b, int m) {
  if (n > m) {
    return FindMedianUtil(b, m, a, n);
  }
  return FindMedianUtil(a, n, b, m);
}
  
int main() {
  int a[] = {9, 12, 15, 900};
  int b[] = {8, 10, 20};
  int n = sizeof(a) / sizeof(a[0]);
  int m = sizeof(b) / sizeof(b[0]);

  cout << FindMedian(a, n, b, m) << endl;
  return 0;
}
