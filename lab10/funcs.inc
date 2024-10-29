#ifndef FUNCS_INC_H
#define FUNCS_INC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SEARCH_LAST // SEARCH_FIRST
#define DELETE_LAST // DELETE_LAST

#define ELEM(array, i) array[i]
#define LEN(array) array[0]
#define TYPE int

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

  // Уменьшаем размер массива
  data = (TYPE *)realloc(data, sizeof(TYPE) * (LEN(data) - N + 1));
  if (data == NULL) {
    return data;
  }

  // Обновляем длину массива
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
}

void cyclicShiftZeroes(int *line, int m)
{
  if (m < 0)
  {
    printf("M must be >= 0\n");
    exit(1);
  }

  int n = ELEM(line, 0);
  int count_zeroes = 0;


  for (int i = 1; i <= n; i++)
  {
    if (ELEM(line, i) == 0)
    {
      count_zeroes++;
    }
  }


  int *zero_indices = (int *)malloc((count_zeroes + 1) * sizeof(int));
  if (zero_indices == NULL)
  {
    printf("Ошибка выделения памяти\n");
    exit(1);
  }

  ELEM(zero_indices, 0) = count_zeroes;

  int index = 1;
  for (int i = 1; i <= n; i++)
  {
    if (ELEM(line, i) == 0)
    {
      ELEM(zero_indices, index) = i;
      index++;
    }
  }


  for (int i = 1; i <= ELEM(zero_indices, 0); i++)
  {
    int new = ELEM(zero_indices, i);
    int count = 0;
    while (count != m)
    {
      if (new == 1)
      {
        int temp = ELEM(line, n);
        ELEM(line, n) = ELEM(line, 1);
        ELEM(line, 1) = temp;
        count++;
        new = n;
        ELEM(zero_indices, i) = n; // Обновляем индекс сдвинутого нуля
      }
      else
      {
        int temp = ELEM(line, new - 1);
        ELEM(line, new - 1) = ELEM(line, new);
        ELEM(line, new) = temp;
        --new;
        count++;
        ELEM(zero_indices, i) = new; // Обновляем индекс сдвинутого нуля
      }

      // Обновляем индексы остальных нулей

    }
  }

  free(zero_indices); 
}

#endif // FUNCS_INC_H
