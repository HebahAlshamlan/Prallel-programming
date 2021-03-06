#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]) {
  int max;
  sscanf (argv[1], "%d", &max);
  int sum = 0;
  #pragma omp parallel for
    for (int i = 1; i <= max; i++)
      #pragma omp critical
        sum = sum + i;
  printf ("%d\n", sum);
  return 0;
}
