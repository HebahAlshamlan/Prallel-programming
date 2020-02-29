#include <stdio.h>
#include <omp.h>

double* vectAdd (double *c, double *a, double *b, int n);
void vectPrint (double *a, int n);

int main (int argc, char *argv[]) {
  int i;
  long n = 15;
  double a[n],b[n],c[n];
  
  for (i = 0; i < n; i++) {
    a[i] = (double) i;
    b[i] = (double) 2*i;
  }

  vectAdd(c, a, b, n);

  printf("\nVector c is: ");
  vectPrint(c,n);

  return 0;
} 

double* vectAdd (double *c, double *a, double *b, int n) { 
  #pragma omp parallel for
    for (int i = 0; i < n; i++){ 
      printf("I am thread %d, adding c[%d].\n", omp_get_thread_num (), i);
      c[i] = a[i] + b[i];
    }
  return c;
}

void vectPrint (double *a, int n) {
    for (int i = 0; i < n; i++)
      printf("%.1f  ", a[i]);
   printf("\n");
}

