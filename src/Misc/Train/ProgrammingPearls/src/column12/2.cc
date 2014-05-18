#include <iostream> // NOLINT
using std::endl;
using std::cout;
#include <cstdlib>

int randint(int m, int n) {
  return m + (rand() / (RAND_MAX / (n - m + 1) + 1));
}

void GenerateM(int m, int n) {
  int i, t;
  i = randint(0, n - 1);
  for(int j = 0; j < m; ++j) {
    t = i + j;
    if (t >= n) {
      t -= n;
    }
    cout << t << " " << endl;
  }
  cout << endl;
}
  
int main(int argc, char *argv[]) {
  const int kM = 10;
  const int kN = 15;
  GenerateM(kM, kN);
  return 0;
}
