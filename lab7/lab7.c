#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(){

  printf("Input N:\n");
  int N;
  scanf("%d", &N);

  double x_min, x_max;
  printf("Enter the minimum value of diaposon: ");
  scanf("%lf %lf", &x_min, &x_max);

  
  double *A = malloc(sizeof(double) * N);
  if (A == NULL){
    printf("error dump");
    return 1;
  }

  srand(time(NULL));
  for (int i = 0; i < N; i++)
  {
    A[i] = x_min + (double)rand() / RAND_MAX * (x_max - x_min);
  }

  for (int i = 0; i < N; i++){
    printf("Value %d: (%.2lf)\n", i + 1, A[i]);
  }
  
  free(A);
  return 0;
}


