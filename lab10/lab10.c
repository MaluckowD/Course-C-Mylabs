#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define DEFAULT_VALUE 100000
#define ELEM(array, i)  array[i]
#define LEN(array)      array[0]
#define TYPE            int

void *delete_element(TYPE *data, TYPE K)
{

  if ((K > LEN(data)) || (K <= 0))
  {
    return data;
  }

  for (TYPE i = K + 1; i <= LEN(data); i++)
  {
    ELEM(data, i - 1) = ELEM(data, i);
  }

  data = (TYPE *)realloc(data, sizeof(TYPE) * LEN(data));
  if (data == NULL)
  {
    return data;
  }

  LEN(data)--;
}

void *search(TYPE *data)
{
  for (TYPE i = 1; i < LEN(data); i++)
  {
    if (ELEM(data, i) % 2 == 0)
    {
      ELEM(data, i) = 0;
      break;
    }
  }
}

void *append(TYPE *data, TYPE K, TYPE N, TYPE a_min, TYPE b_max)
{
  srand(time(NULL));
  if ((K > LEN(data)) || (K <= 0) || N <= 0)
  {
    return data;
  }

  data = (TYPE *)realloc(data, sizeof(TYPE) * (LEN(data) + N + 1));
  if (data == NULL)
  {
    return data;
  }

  for (TYPE i = LEN(data); i >= K; i--)
  {
    ELEM(data, (i + N)) = ELEM(data, i);
  }

  for (TYPE i = K; i < K + N; i++)
  {
    ELEM(data, i) = rand() % (b_max - a_min + 1) + a_min;
  }

  LEN(data) += N;
}

void *cyclicShiftZeroes(TYPE *line, TYPE m)
{
  if (m < 0)
  {
    printf("M must be >= 0\n");
    exit(1);
  }

  TYPE n = line[0];

  TYPE *zeroes = (TYPE *)malloc(n * sizeof(TYPE));
  if (zeroes == NULL)
  {
    printf("Segmentation error!\n");
    exit(1);
  }

  TYPE zeroes_counter = 0;

  for (TYPE i = 1; i <= n; ++i)
    if (line[i] == 0)
      zeroes[zeroes_counter++] = (i - 1 - m + n) % n + 1;

  TYPE *new_line = (TYPE *)malloc((n + 1) * sizeof(TYPE));
  if (new_line == NULL)
  {
    printf("Segmentation error!\n");
    exit(1);
  }
  new_line[0] = line[0];

  for (TYPE i = 1; i <= n; ++i)
    new_line[i] = DEFAULT_VALUE;

  for (TYPE i = 0; i < zeroes_counter; ++i)
    new_line[zeroes[i]] = 0;

  TYPE ptr = 1;
  for (TYPE i = 1; i <= n; ++i)
  {
    if (new_line[i] == DEFAULT_VALUE)
    {
      while (line[ptr] == 0)
        ptr++;
      new_line[i] = line[ptr];
      ptr++;
    }
  }

  free(zeroes);
  free(line);

  return new_line;
}

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
      search(ELEM(ar, i));
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