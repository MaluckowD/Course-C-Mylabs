#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SEARCH_LAST // SEARCH_FIRST SEARCH_LAST
#define RIGHT_SHIFT // LEFT_SHIFT

#define DEFAULT_VALUE 100000
#define ELEM(array, i) array[i]
#define LEN(array) array[0]
#define TYPE int

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

  LEN(data)
  --;
}

#if defined(SEARCH_FIRST)
void *search_first(TYPE *data)
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
#else
void *search_last(TYPE *data)
{
  for (TYPE i = LEN(data); i >= 0; i--)
  {
    if (ELEM(data, i) % 2 == 0)
    {
      ELEM(data, i) = 0;
      break;
    }
  }
}
#endif

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
