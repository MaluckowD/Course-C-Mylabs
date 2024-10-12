#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{

  int N;
  printf("Input N: ");
  scanf("%d", &N);

  int x_min, x_max;
  printf("Enter the minimum value of the range: ");
  scanf("%d", &x_min);
  printf("Enter the maximum value of the range: ");
  scanf("%d", &x_max);

  int *A = (int *)malloc(sizeof(int) * N);
  if (A == NULL)
  {
    return 1;
  }
  int *A1 = (int *)malloc(sizeof(int) * N);
  if (A1 == NULL)
  {
    return 1;
  }
  int *A2 = (int *)malloc(sizeof(int) * N);
  if (A2 == NULL)
  {
    return 1;
  }

  srand(time(NULL));
  for (int i = 0; i < N; i++)
  {
    *(A + i) = rand() % (x_max - x_min + 1) + x_min;
  }

  int count1 = 0;
  int count2 = 0;
  printf("Massive A: \n");
  for (int i = 0; i < N; i++)
  {
    int count = 0;
    printf("%d\n", A[i]);
    for (int j = 1; j <= abs(A[i]); j++)
    {
      if (abs(A[i]) % j == 0)
      {
        count++;
      }
    }
    if (count == 2)
    {
      int el = A[i];
      int number_digits = 0;
      while (el != 0)
      {
        number_digits++;
        el = el / 10;
      }
      if (number_digits % 2 == 0)
      {
        A2[count2] = A[i];
        count2++;
      }
      else
      {
        A1[count1] = A[i];
        count1++;
      }
    }
  }

  int *B = (int *)malloc(sizeof(int) * (count1 + count2));
  if (B == NULL)
  {
    return 1;
  }
  for (int i = 0; i < count1; i++)
  {
    B[i] = A1[i];
  }
  for (int i = 0; i < count2; i++)
  {
    B[i + count1] = A2[i];
  }
  printf("Massive B: \n");
  for (int i = 0; i < count1 + count2; i++)
  {
    printf("%d ", B[i]);
  }

  free(A);
  free(A1);
  free(A2);
  free(B);
  return 0;
}
