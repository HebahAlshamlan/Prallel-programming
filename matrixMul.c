#include <stdio.h>
#include <omp.h>
#define  N 3

void mtxMul (int c[][N], int a[][N], int b[][N], int n);

int main (int argc, char *argv[]) {
  int a[N][N] = { {1, 1, 1}, 
                  {2, 2, 2}, 
                  {3, 3, 3} }; 
  
  int b[N][N] = { {1, 1, 1},     
                  {2, 2, 2},
                  {3, 3, 3} }; 
  
  int c[N][N];
  
  mtxMul(c,a,b,N);

  printf("Matrices a,b are 3*3, we expect 9 threads.\n");

  int i, j; 
  printf("Result matrix is \n"); 
  for (i = 0; i < N; i++) { 
    for (j = 0; j < N; j++) 
       printf("%d ", c[i][j]); 
     printf("\n"); 
  } 
  return 0;
} 

void mtxMul (int c[][N], int a[][N], int b[][N], int n) {
  #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) 
      for (int j = 0; j < n; j++) {
        printf("I am thread %d\n",omp_get_thread_num() );
        c[i][j] = 0.0;
        for (int k = 0; k < n; k++)
          c[i][j] = c[i][j] + a[i][k] * b[k][j];
      }
}


