#include <iostream>  // NOLINT
using std::cout;
using std::endl;
#include <stack>
using std::stack;

bool FindMoreThanHalf(int *array, int n, int *res) {
  stack<int> stk;
  int i;
  for (i = 0; i < n; ++i) {
    if (stk.empty()) {
      stk.push(array[i]);
    } else {
      if (stk.top() == array[i]) {
        stk.push(array[i]);
      } else {
        stk.pop();
      }
    }
  }
  if (stk.empty()) {
    return false;
  }
  int candidate = stk.top();
  int times = 0;
  for (i = 0; i < n; ++i) {
    if (array[i] == candidate) {
      times++;
    }
  }
  if (times > n / 2) {
    *res = candidate;
    return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  const int kN = 10;
  int array[kN];
  int i;
  for (i = 0; i < kN; ++i) {
    array[i] = i;
  }
  for (; i < kN; ++i) {
    array[i] = kN - 1;
  }
  int res;
  if (FindMoreThanHalf(array, kN, &res)) {
    cout << "the element more than N/2 is: " << res << endl;
  } else {
    cout << "there is no element more than N/2 times" << endl;
  }
  return 0;
}
