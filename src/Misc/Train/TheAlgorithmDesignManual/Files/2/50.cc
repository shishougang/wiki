#include <iostream>  // NOLINT
using std::cout;
using std::endl;
#include <vector>
using std::vector;

bool FindEqual(const vector<int> &num_cube, int low, int high, const int &sum,
               vector<int> *res) {
  if (low >= high) {
    return false;
  }
  int i, j;
  i = low;
  j = high;
  int add;
  while (i < j) {
    add = num_cube[i] + num_cube[j];
    if (add == sum) {
      res->push_back(i);
      res->push_back(j);
      return true;
    }
    if (add > sum) {
      --j;
    } else {
      ++i;
    }
  }
  return false;
}

void RamanujamNum(int n, vector<vector<int> > *res) {
  vector<int> num_cube(n);
  int i, j;
  for (i = 0; i < n; ++i) {
    num_cube[i] = i*i*i;
  }
  vector<int> ram_num;
  bool find;
  for (i = 0; i < n - 1; ++i) {
    for (j = i + 3; j < n; ++j) {
      find = FindEqual(num_cube, i+1, j-1, num_cube[i] + num_cube[j], &ram_num);
      if (find) {
        ram_num.push_back(i);
        ram_num.push_back(j);
        res->push_back(ram_num);
        ram_num.clear();
      }
    }
  }
}


int main(int argc, char *argv[]) {
  vector<vector<int > > ramanujam_num;
  RamanujamNum(100, &ramanujam_num);
  for (int i = 0; i < ramanujam_num.size(); ++i) {
    for (int j = 0; j < ramanujam_num[i].size(); ++j) {
      cout << ramanujam_num[i][j] << ",";
    }
    cout << endl;
  }
  return 0;
}
