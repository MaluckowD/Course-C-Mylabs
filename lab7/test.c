#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{

  int N;
  printf("Input N:\n");
  scanf("%d", &N);

  double x_min, x_max;
  printf("Enter the minimum value of the range: ");
  scanf("%lf", &x_min); // Ввод минимального значения
  printf("Enter the maximum value of the range: ");
  scanf("%lf", &x_max); // Ввод максимального значения

  double *A = (double *)malloc(sizeof(double) * N);
  if (A == NULL)
  {
    return 1;
  }
  
  srand(time(NULL));
  for (int i = 0; i < N; i++)
  {
    *(A+i) = x_min + (double)rand() / RAND_MAX * (x_max - x_min);
  }

  for (int i = 0; i < N; i++)
  {
    printf("Value %d: (%.2lf)\n", i + 1, A[i]);
  }

  free(A);
  return 0;
}