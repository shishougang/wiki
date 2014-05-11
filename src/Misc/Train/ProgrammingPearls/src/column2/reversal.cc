#include <iostream>  //NOLINT
using std::cout;
using std::endl;

void reverse(char *array, int s, int e) {
  while (s < e) {
    int temp = array[s];
    array[s] = array[e];
    array[e] = temp;
    s++;
    e--;
  }
}
void rotate(char *array, int n, int k) {
  reverse(array, 0, k - 1);
  reverse(array, k, n - 1);
  reverse(array, 0, n - 1);
}

int main(int argc, char *argv[]) {
  char a[] = "abcdefgh";
  rotate(a, 8, 3);
  cout << a << endl;
  return 0;
}
