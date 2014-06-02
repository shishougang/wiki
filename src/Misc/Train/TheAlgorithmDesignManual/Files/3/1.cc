#include <iostream>  // NOLINT
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <stack>
using std::stack;

bool BalancedParentheses(string parentheses, int *pos) {
  stack<int> stk;
  const int kLeftPar = 1;
  int i;
  for (i = 0; i < parentheses.size(); ++i) {
    if (parentheses[i] == '(') {
      stk.push(kLeftPar);
    } else {
      if (stk.empty()) {
        *pos = i;
        return false;
      }
      stk.pop();
    }
  }
  if (!stk.empty()) {
    *pos = --i;
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  string parentheses = "((())())()";
  bool res;
  int pos;
  res = BalancedParentheses(parentheses, &pos);
  if (res) {
    cout << parentheses << "has balanced parentheses" << endl;
  }
  parentheses = ")()(";
  res = BalancedParentheses(parentheses, &pos);
  if (!res) {
    cout << parentheses << " has unbalanced parentheses at " << pos << endl;
  }
  return 0;
}
