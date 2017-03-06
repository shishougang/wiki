#include <iostream>
#include <vector>

using namespace std;

int LIS(const vector<int> &vec) {
  int n = vec.size();
  int lis[n];
  int max_lis = 0;
  int i, j;

  for (i = 0; i < n; ++i) {
    lis[i] = 1;
  }

  for (i = 1; i < n; ++i) {
    for(j = 0; j < i; ++j) {
      if (vec[i] > vec[j] && lis[i] < lis[j] + 1) {
        lis[i] = lis[j] + 1;
      }
      max_lis = max(max_lis, lis[i]);
    }
  }
  return max_lis;
}

int main() {
  int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
  vector<int> vec(arr, arr + sizeof(arr) / sizeof(int));
  cout << "Length of lis is " << LIS(vec) << endl;
  return 0;
}
