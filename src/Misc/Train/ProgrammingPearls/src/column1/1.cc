#include <cstdlib>
#include <cstdio>

int comp(const void *a, const void *b) {
  return (*reinterpret_cast<const int *>(a) -
          *reinterpret_cast<const int *>(b));
}

int main(int argc, char *argv[]) {
  int n = 0;
  int array[10000];
  while (scanf("%d", &array[n]) != EOF) {
    ++n;
  }
  qsort(array, n, sizeof(int), comp);
  for (int i = 0; i < n; ++i) {
      printf("%d\n", array[i]);
  }
  return 0;
}
