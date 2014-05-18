#include <iostream> // NOLINT
using std::endl;
using std::cout;
#include <cstdlib>
#include <set>
using std::multiset;

int randint(int m, int n) {
  return m + (rand() / (RAND_MAX / (n - m + 1) + 1));
}

int compare(const void *a, const void *b) {
  return (*static_cast<const int*>(a) - *static_cast<const int*>(b));
}

void GenShuf(int m, int n) {
  int *x = new int[n];
  int i = 0;
  for (i = 0; i < n; ++i) {
    x[i] = i;
  }
  for (i = 0; i < m; ++i) {
    int j = randint(i, n - 1);
    int t = x[j];
    x[j] = x[i];
    x[i] = t;
  }

  for (i = 0; i < m; ++i) {
    cout << x[i] << " ";
  }
  cout << endl;
  delete x;
}

void GenSets(int m, int n) {
  multiset<int> num_set;
  while (num_set.size() < m) {
    num_set.insert(rand() % n);
  }
  for (multiset<int>::iterator it = num_set.begin(); it != num_set.end();
       ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

void GenM(int m, int n) {
  for (int i = 0; i < m; ++i) {
    cout << randint(0, n - 1) << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  const int kM = 10;
  const int kN = 100;
  GenShuf(kM, kN);
  GenSets(kM, kN);
  GenM(kM, kN);
  return 0;
}
