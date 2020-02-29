#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]) {
  int max;
  sscanf (argv[1], "%d", &max);
 
  printf("omp_get_nested() = %d\n", omp_get_nested());

  #pragma omp parallel for
    for (int i = 1; i <= max; i++) {
      printf ("Number of threads in outer team %d: \n", omp_get_num_threads());
      printf("I am outer thread %d\n", omp_get_thread_num ()); 
      #pragma omp parallel for
        for (int j = 1; j <= max; j++) {
          printf ("Number of threads in inner team %d: \n", omp_get_num_threads());
          printf ("I am inner thread %d: (%d,%d)\n", omp_get_thread_num (), i, j);
        }
     }
  return 0;
}
