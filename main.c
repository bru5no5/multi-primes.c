#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int is_prime(int num) {
  if (num <= 1) return 0;
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) return 0;
  }
  return 1;
}

void *find_primes(void *arg) {
  int *params = (int *)arg;
  int start = params[0];
  int end = params[1];
  printf("Thread procurando de %d até %d\n", start, end);
  for (int i = start; i <= end; i++) {
    if (is_prime(i)) {
      printf("%d é primo\n", i);
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("Uso: %s J K NTHREADS(opcional)\n", argv[0]);
    return 1;
  }

  int start = atoi(argv[1]);
  int end = atoi(argv[2]);
  int num_threads = argc >= 4 ? atoi(argv[3]) : atoi(getenv("NTHREADS"));

  pthread_t threads[num_threads];
  int params[num_threads][2];
  int range = (end - start + 1) / num_threads;

  for (int i = 0; i < num_threads; i++) {
    params[i][0] = start + i * range;
    params[i][1] = (i == num_threads - 1) ? end : params[i][0] + range - 1;
    pthread_create(&threads[i], NULL, find_primes, (void *)params[i]);
  }

  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }
  
  return 0;
}
