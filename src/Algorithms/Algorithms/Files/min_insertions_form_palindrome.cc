#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

int FindMinInsertions(char *str, int l, int h) {
  if (l > h) {
    return INT_MAX;
  }
  if (l == h) {
    return 0;
  }
  if (l == h - 1) {
    return (str[l] == str[h])? 0 : l;
  }
  if (str[l] == str[h]) {
    return FindMinInsertions(str, l+1, h-1);
  } else {
    return (min(FindMinInsertions(str, l+1, h),
                FindMinInsertions(str, l, h-1)) + 1);
  }
}

int main() {
  char str[] = "geeks";
  cout << FindMinInsertions(str, 0, strlen(str)-1) << endl;
  return 0;
}
