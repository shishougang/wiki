#include <iostream>
#include <stack>
#include <limits>
using namespace std;


bool CanRepresentBST(int *pre, int n) {
  stack<int> stk;
  int root = numeric_limits<int>::min();
  for (int i = 0; i < n; ++i) {
    if (root > pre[i]) {
      return false;
    }
    while (!stk.empty() && stk.top() < pre[i]) {
      root = stk.top();
      stk.pop();
    }
    stk.push(pre[i]);
  }
  return true;
}

int main() {
  int pre1[] = {40, 30, 35, 80, 100};
  int n = sizeof(pre1)/sizeof(pre1[0]);
  CanRepresentBST(pre1, n)? cout << "true\n":
      cout << "false\n";

  int pre2[] = {40, 30, 35, 20, 80, 100};
  n = sizeof(pre2)/sizeof(pre2[0]);
  CanRepresentBST(pre2, n)? cout << "true\n":
      cout << "false\n";
  return 0;
}
