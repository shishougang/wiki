
int randint(int m, int n) {
  return m + (rand() / (RAND_MAX / (n - m + 1) + 1));
}

int bigrand() {
  return RAND_MAX * rand() + rand();
}
