#include <iostream>  //NOLINT
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <algorithm>
using std::max;

float FindMaxSubvectorAlg1(const vector<float> &num) {
  int i, j, k;
  float sum, max_sofar;
  max_sofar = 0;
  for (i = 0; i < num.size(); ++i) {
    for (j = 0; j < num.size(); ++j) {
      sum = 0;
      for (k = i; k <= j; k++) {
        sum += num[k];
        if (sum > max_sofar) {
          max_sofar = sum;
        }
      }
    }
  }
  return max_sofar;
}

float FindMaxSubvectorAlg2(const vector<float> &num) {
  int i, j;
  float sum, max_sofar;
  max_sofar = 0;
  for (i = 0; i < num.size(); ++i) {
    sum = 0;
    for (j = i; j < num.size(); ++j) {
      sum += num[j];
      if (sum > max_sofar) {
        max_sofar = sum;
      }
    }
  }
  return max_sofar;
}

float FindMaxSubvectorAlg2b(const vector<float> &num) {
  vector<float> cum_vector(num.size() + 1);
  int i, j;
  cum_vector[0] = 0;
  for (i = 1; i < cum_vector.size(); ++i) {
    cum_vector[i] = cum_vector[i - 1] + num[i];
  }
  float sum, max_sofar;
  max_sofar = 0;
  for (i = 1; i < cum_vector.size(); ++i) {
    for (j = i; j < cum_vector.size(); ++j) {
      sum = cum_vector[j] - cum_vector[i - 1];
      if (sum > max_sofar) {
        max_sofar = sum;
      }
    }
  }
  return max_sofar;
}

float FindMaxSubvectorAlg3Core(const vector<float> &num, int l, int u) {
  if (l > u) {
    return 0;
  }
  if (l == u) {
    return max<float>(num[l], 0);
  }
  int m;
  m = (l + u) / 2;
  float lmax, rmax, sum;
  lmax = sum = 0;
  for (int i = m; i >= l; --i) {
    sum += num[i];
    if (sum > lmax) {
      lmax = sum;
    }
  }
  rmax = sum = 0;
  for (int i = m + 1; i <= u; ++i) {
    sum += num[i];
    if (sum > rmax) {
      rmax = sum;
    }
  }
  return max(lmax + rmax, max(FindMaxSubvectorAlg3Core(num, l, m),
                              FindMaxSubvectorAlg3Core(num, m + 1, u)));
}

float FindMaxSubvectorAlg3(const vector<float> &num) {
  return FindMaxSubvectorAlg3Core(num, 0, num.size() - 1);
}

float FindMaxSubvectorAlg4(const vector<float> &num) {
  float max_sofar, max_ending_here;
  max_sofar = max_ending_here = 0;
  for (int i = 0; i < num.size(); ++i) {
    max_ending_here += num[i];
    if (max_ending_here < 0) {
      max_ending_here = 0;
    }
    if (max_ending_here > max_sofar) {
      max_sofar = max_ending_here;
    }
  }
  return max_sofar;
}

void GenerateDataVector(vector<float> *num, int n) {
  num->resize(n);
  for (int i = 0; i < n; ++i) {
    (*num)[i] = 1.0 - 2 * (static_cast<float>(rand()) / RAND_MAX);
  }
}


int main(int argc, char *argv[]) {
  vector<float> num;
  const int kMaxN = 10000;
  GenerateDataVector(&num, kMaxN);
  cout << "Max Subvector Alg1:" << FindMaxSubvectorAlg1(num) << endl;
  cout << "Max Subvector Alg2:" << FindMaxSubvectorAlg2(num) << endl;
  cout << "Max Subvector Alg2b:" << FindMaxSubvectorAlg2b(num) << endl;
  cout << "Max Subvector Alg3:" << FindMaxSubvectorAlg3(num) << endl;
  cout << "Max Subvector Alg4:" << FindMaxSubvectorAlg4(num) << endl;
  return 0;
}
