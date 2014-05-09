#include <cstdio>
#include <cstdlib>
#include <utility>
#include <ctime>

unsigned int seed = time(NULL);
int randint(int m, int n) {
  return m + rand_r(&seed) / (RAND_MAX / (n + 1 - m) + 1);
}

void generate_unique_random(const int n, const int k, int *out) {
  int num[n];
  int i;
  for(i = 0; i < n; ++i) {
    num[i] = i;
  }
  for(i = 0; i < k; ++i) {
    int p = randint(i, n - 1);
    std::swap(num[i], num[p]);
    out[i] = num[i];
  }
}

#define N 1000000
#define K 100
int main(int argc, char *argv[])
{
  int out[K];
  generate_unique_random(N, K, out);
  for (int i = 0; i < K; ++i) {
    printf("%d\n", out[i]);
  }
  return 0;
}
