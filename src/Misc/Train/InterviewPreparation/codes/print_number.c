#include <stdio.h>
#include <pthread.h>

pthread_t odd_thread, even_thread;
pthread_mutex_t lock;
pthread_cond_t cond;

int is_even;

void* even_print(void *data) {
  int *max = data;
  int i;
  for (i = 0; i < *max; i += 2) {
    pthread_mutex_lock(&lock);
    while (is_even != 1) {
      pthread_cond_wait(&cond, &lock);
    }
    is_even = 0;
    printf("%d, ", i);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

void* odd_print(void *data) {
  int *max = data;
  int i;
  for (i = 1; i < *max; i += 2) {
    pthread_mutex_lock(&lock);
    while (is_even != 0) {
      pthread_cond_wait(&cond, &lock);
    }
    is_even = 1;
    printf("%d, ", i);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  int max = 100;
  is_even = 1;
  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&lock, NULL);
  pthread_create(&even_thread, NULL, &even_print, &max);
  pthread_create(&odd_thread, NULL, &odd_print, &max);
  pthread_join(even_thread, NULL);
  pthread_join(odd_thread, NULL);
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&cond);
  return 0;
}
