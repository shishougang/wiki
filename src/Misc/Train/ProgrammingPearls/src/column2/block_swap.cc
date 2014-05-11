#include <iostream>  //NOLINT
using std::cout;
using std::endl;

void swap(char *array, int m, int n, int len) {
  //swap array[m..m+len], array[n..n+len]
  for(int i = 0; i < len; ++i) {
    int temp = array[m + i];
    array[m + i] = array[n + i];
    array[n + i] = temp;
  }
}

void rotate(char *array, int n, int k) {
  if (k == 0 || k == n) {
    return;
  }
  /* array[0..p-i-1]:final stage
   * array[p-i..p-1]:the string a to be swaped
   * array[p..p+j-1]:the string b to be swaped
   * array[p+j..n-1]:final stage
   */
  int p = k;
  int i = k;
  int j = n - k;
  while (i != j) {
    if (i < j) {
      swap(array, p - i, p + j - i, i);
      j -= i;
    } else {
      swap(array, p - i, p, j);
      i -= j;
    }
  }
  swap(array, p - i, p, i);
}

int main(int argc, char *argv[]) {
  char a[] = "abcdefgh";
  rotate(a, 8, 3);
  cout << a << endl;
  return 0;
}
