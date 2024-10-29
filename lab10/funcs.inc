#ifndef FUNCS_INC
#define FUNCS_INC

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SEARCH_LAST // SEARCH_FIRST
#define DELETE_LAST // DELETE_ELEM

#define ELEM(array, i) array[i]
#define LEN(array) array[0]
#define TYPE int

void *cyclicShiftZeroes(TYPE *line, int m)
{
  if (m < 0)
  {
    printf("M must be >= 0\n");
    exit(1);
  }
  TYPE n = LEN(line);
  bool visited[1000];
  for (TYPE k = 1; k <= m; k++){

    for (TYPE i = 1; i <= n; i++)
    {
      ELEM(visited, i) = false;
    }
    for (TYPE i = 1; i <= LEN(line); i++){
      if (ELEM(line, i) == 0 && ELEM(visited, i) == false){
        if (i == 1)
        {
          for (TYPE i = 1; i <= LEN(line); i++)
          {
            ELEM(line, i) = line[i + 1];
          }
          ELEM(line, n) = 0;
          ELEM(visited, n) = true;
        }
        else
        {
          TYPE temp = ELEM(line, i - 1);
          ELEM(line, i - 1) = ELEM(line, i);
          ELEM(line, i) = temp;
          ELEM(visited, i - 1) = true;
        }
      }
    }
  }
}

#if defined(DELETE_ELEM)
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
#else
void *delete_last_elements(TYPE *data, TYPE N) {
  if ((N > LEN(data)) || (N <= 0)) {
    return data;
  }

  data = (TYPE *)realloc(data, sizeof(TYPE) * (LEN(data) - N + 1));
  if (data == NULL) {
    return data;
  }

  LEN(data) -= N;
  return data;
}
#endif

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
  return data;
}

#endif
