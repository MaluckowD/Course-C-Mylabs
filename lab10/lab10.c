#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "./funcs.inc.h"

TYPE main()
{

  TYPE A, B;
  printf("Input A, B: \n");
  scanf("%d %d", &A, &B);
  if ((A < 0) && (B < 0))
  {
    printf("Input correct A and B\n");
    return 0;
  }
  TYPE a_min, b_max;
  printf("Input Enter the left and right generation range: \n");
  scanf("%d %d", &a_min, &b_max);
  if (a_min >= b_max)
  {
    printf("Input correct a_min < b_max\n");
    return 0;
  }

  printf("The original matrix:\n");
  TYPE **ar = (TYPE **)malloc(A * sizeof(TYPE *));
  if (ar == NULL)
  {
    printf("Error: Memory allocation failed\n");
    return 1;
  }

  for (TYPE i = 0; i < A; i++)
  {
    ELEM(ar, i) = (TYPE *)malloc((B + 1) * sizeof(TYPE));
    if (ELEM(ar, i) == NULL)
    {
      printf("Error: Memory allocation failed\n");
      for (TYPE j = 0; j < i; j++)
      {
        free(ELEM(ar, j));
      }
      free(ar);
      return 1;
    }
  }

  for (TYPE i = 0; i < A; i++)
  {
    ELEM(ar,i)[0] = B;
  }

  srand(time(NULL));
  for (TYPE i = 0; i < A; i++)
  {
    for (TYPE j = 1; j < B + 1; j++)
    {
      ELEM(ar, i)[j] = rand() % (b_max - a_min + 1) + a_min;
    }
  }

  for (TYPE i = 0; i < A; i++)
  {
    for (TYPE j = 0; j < ELEM(ar, i)[0] + 1; j++)
    {
      printf("%d ", ELEM(ar, i)[j]);
    }
    printf("\n");
  }

  TYPE K;
  printf("Input index element: \n");
  scanf("%d", &K);

  TYPE N;
  printf("Enter the number of numbers you want to add: \n");
  scanf("%d", &N);

  TYPE M;
  printf("Enter the offset for the zeros: \n");
  scanf("%d", &M);

  for (TYPE i = 0; i < A; i++)
  {
    if (i % 4 == 0)
    {
      delete_element(ELEM(ar, i), K);
    }
    else if (i % 4 == 1)
    {
      ELEM(ar, i) = append(ELEM(ar, i), K, N, a_min, b_max);
    }
    else if (i % 4 == 2)
    {
      ELEM(ar, i) = cyclicShiftZeroes(ELEM(ar, i), M);
    }
    else
    {
#ifdef SEARCH_FIRST
      search_first(ELEM(ar, i));
#else
      search_last(ELEM(ar, i));
#endif
    }
  }
  printf("The final matrix: \n");
  for (TYPE i = 0; i < A; i++)
  {
    for (TYPE j = 0; j < ELEM(ar, i)[0] + 1; j++)
    {
      if (j == ELEM(ar, i)[0])
      {
        printf("%d\n", ELEM(ar, i)[j]);
        break;
      }

      printf("%d ", ELEM(ar, i)[j]);
    }
    printf("\n");
  }

  for (TYPE i = 0; i < A; i++)
  {
    free(ELEM(ar, i));
  }
  free(ar);

  return 0;

}