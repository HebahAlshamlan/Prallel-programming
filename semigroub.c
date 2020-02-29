#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]) {
  int max; sscanf (argv[1], "%d", &max);
  int ts = omp_get_max_threads();

  int sums[ts];
  #pragma omp parallel
	{
	int t = omp_get_max_threads();
	int lo = (max/ts)*(t+0)+1;
	int hi = (max/ts)*(t+1)+0;
	for (int i = lo ; i<= hi ; i++)
	sums[t]=sums[t]+i;
	}

  int sum = 1 ;

  for (int t = 0 ; t<ts ; t++) 
	{

sums[t+sum]=sums[t]+sums[t+sum];
sum=sum*2;
  printf(" this is the sum %d \n ",sum);
}


 printf(" this is the final sum %d \n ",sum);
  return 0;

}
