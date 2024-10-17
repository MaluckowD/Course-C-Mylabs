#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

int main()
{

  int A, B;
  printf("Input A, B: \n");
  scanf("%d %d", &A, &B);
  int a_min, b_max;
  printf("Input Enter the left and right generation range: \n");
  scanf("%d %d", &a_min, &b_max);

  int **coords = (int **)malloc(A * sizeof(int *)); 
  if (coords == NULL)
  {
    printf("Error: Memory allocation failed\n");
    return NULL;
  }

  for (int i = 0; i < A; i++)
  {
    coords[i] = (int *)malloc((B + 1)  * sizeof(int));
    if (coords[i] == NULL)
    {
      printf("Error: Memory allocation failed\n");
      for (int j = 0; j < i; j++)
      {
        free(coords[j]);
      }
      free(coords);
      return NULL;
    }
  }
  for (int i = 0; i < A; i++)
  {
    coords[i][0] = B;
  }

  srand(time(NULL));
  for (int i = 0; i < A; i++)
  {
    for (int j = 1; j < B + 1; j++)
    {
      coords[i][j] = rand() % (b_max - a_min + 1) + a_min;
    }
  }

  for (int i = 0; i < A; i++)
  {
    for (int j = 0; j < B + 1; j++)
    {
      printf("%d ", coords[i][j]); // Исправлено!
    }
    printf("\n"); // Добавлен вывод новой строки
  }

  // Освобождение выделенной памяти
  for (int i = 0; i < A; i++)
  {
    free(coords[i]);
  }
  free(coords);

  return 0;
}