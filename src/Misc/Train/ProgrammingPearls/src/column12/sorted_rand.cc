#include <iostream> // NOLINT
using std::endl;
using std::cout;
#include <cstdlib>
#include <set>
using std::set;

int randint(int m, int n) {
  return m + (rand() / (RAND_MAX / (n - m + 1) + 1));
}

void GenerateSortedRand(int m, int n) {
  int select = m;
  int remaining = n;
  for (int i = 0; i < n && select > 0; ++i) {
    if (rand() % remaining < select) {
      cout << i << " ";
      --select;
    }
    --remaining;
  }
  cout << endl;
}

void GenKnuth(int m, int n) {
  for (int i = 0; i < n && m > 0; ++i) {
    if (rand() % (n - i) < m) {
      cout << i << " ";
      --m;
    }
  }
  cout << endl;
}

void GenSets(int m, int n) {
  set<int> num_set;
  while (num_set.size() < m) {
    num_set.insert(rand() % n);
  }
  for (set<int>::iterator it = num_set.begin(); it != num_set.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
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
  qsort(x, m, sizeof(int), compare);
  for (i = 0; i < m; ++i) {
    cout << x[i] << " ";
  }
  cout << endl;
  delete x;
}

int main(int argc, char *argv[]) {
  const int kM = 10;
  const int kN = 100;
  GenerateSortedRand(kM, kN);
  GenKnuth(kM, kN);
  GenSets(kM, kN);
  GenShuf(kM, kN);
  return 0;
}
