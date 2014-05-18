#include <iostream> // NOLINT
using std::endl;
using std::cout;
#include <cstdlib>
#include <set>
using std::set;

int randint(int m, int n) {
  return m + (rand() / (RAND_MAX / (n - m + 1) + 1));
}

void GenSets(int m, int n) {
  set<int> num_set;
  int t;
  for (int i = n - m ; i < n; ++i) {
    t = randint(0, i);
    if (num_set.find(t) == num_set.end()) {
      num_set.insert(t);
    } else {
      num_set.insert(i);
    }
  }
  for (set<int>::iterator it = num_set.begin(); it != num_set.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  const int kM = 10;
  const int kN = 100;    
  GenSets(kM, kN);
  return 0;
}
