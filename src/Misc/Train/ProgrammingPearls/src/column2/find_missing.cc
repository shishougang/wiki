#include <iostream>
using std::cout;
using std::endl;

int find_missing(int *array, int len, int nbits) {
  int leading_zero[len / 2 + 1];
  int leading_one[len / 2 + 1];
  int n = len;
  int res = 0;
  int *p_in = array;

  while (nbits--) {
    int count_leading_zero = 0;
    int count_leading_one = 0;
    int leading_bit = 1 << nbits;
    for (int i = 0; i < n; ++i) {
      if (p_in[i] & leading_bit) {
        leading_one[count_leading_one++] = p_in[i];
      } else {
        leading_zero[count_leading_zero++] = p_in[i];
      }
    }
    if (count_leading_one <= count_leading_zero) {
      res |= leading_bit;
      n = count_leading_one;
      p_in = leading_one;
    } else {
      n = count_leading_zero;
      p_in = leading_zero;
    }
  }
  return res;
}

int main(int argc, char *argv[]) {
  int a[7];
  int missing_num = 5;
  for (int i = 0; i < 7; ++i) {
    if (i != missing_num) {
      a[i] = i;
    }
  }
  cout << find_missing(a, 7, 3) << endl;;
  return 0;
}
