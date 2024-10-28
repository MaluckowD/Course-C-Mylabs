#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define DEFAULT_VALUE 100000

void *delete_element(int *data, int K)
{

  if ((K > data[0]) || (K <= 0))
  {
    return data;
  }

  for (int i = K + 1; i <= data[0]; i++)
  {
    data[i - 1] = data[i];
  }

  data = (int *)realloc(data, sizeof(int) * (data[0]));
  if (data == NULL)
  {
    return data; 
  }

  data[0]--;

}

void *search(int *data)
{
  for (int i = 1; i < data[0]; i++)
  {
    if (data[i] % 2 == 0)
    {
      data[i] = 0;
      break;
    }
  }
}

void *append(int *data, int K, int N, int a_min, int b_max)
{
  srand(time(NULL));
  if ((K > data[0]) || (K <= 0) || N <= 0)
  {
    return data;
  }

  data = (int *)realloc(data, sizeof(int) * (data[0] + N + 1));
  if (data == NULL)
  {
    return data;
  }

  for (int i = data[0]; i >= K; i--)
  {
    data[i + N] = data[i];
  }

  for (int i = K; i < K + N; i++)
  {
    data[i] = rand() % (b_max - a_min + 1) + a_min;
  }

  data[0] += N;

}
void cyclicShiftZeroes(int *line, int m)
{
  if (m < 0)
  {
    printf("M must be >= 0\n");
    exit(1);
  }

  int n = line[0];
  int count_zeroes = 0;


  for (int i = 1; i <= n; i++)
  {
    if (line[i] == 0)
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
  zero_indices[0] = count_zeroes;

  int index = 1;
  for (int i = 1; i <= n; i++)
  {
    if (line[i] == 0)
    {
      zero_indices[index] = i;
      index++;
    }
  }


  for (int i = 1; i <= zero_indices[0]; i++)
  {
    int new = zero_indices[i];
    int count = 0;
    while (count != m)
    {
      if (new == 1)
      {
        int temp = line[n];
        line[n] = line[1];
        line[1] = temp;
        count++;
        new = n;
        zero_indices[i] = n; // Обновляем индекс сдвинутого нуля
      }
      else
      {
        int temp = line[new - 1];
        line[new - 1] = line[new];
        line[new] = temp;
        --new;
        count++;
        zero_indices[i] = new; // Обновляем индекс сдвинутого нуля
      }

      // Обновляем индексы остальных нулей

    }
  }

  free(zero_indices); 
}

int main()
{

  int A, B;
  printf("Input A, B: \n");
  scanf("%d %d", &A, &B);
  if ((A < 0) && (B < 0))
  {
    printf("Input correct A and B\n");
    return 0;
  }
  int a_min, b_max;
  printf("Input Enter the left and right generation range: \n");
  scanf("%d %d", &a_min, &b_max);
  if (a_min >= b_max)
  {
    printf("Input correct a_min < b_max\n");
    return 0;
  }

  printf("The original matrix:\n");
  int **ar = (int **)malloc(A * sizeof(int *));
  if (ar == NULL)
  {
    printf("Error: Memory allocation failed\n");
    return 1;
  }

  for (int i = 0; i < A; i++)
  {
    ar[i] = (int *)malloc((B + 1) * sizeof(int));
    if (ar[i] == NULL)
    {
      printf("Error: Memory allocation failed\n");
      for (int j = 0; j < i; j++)
      {
        free(ar[j]);
      }
      free(ar);
      return 1;
    }
  }

  for (int i = 0; i < A; i++)
  {
    ar[i][0] = B;
  }

  srand(time(NULL));
  for (int i = 0; i < A; i++)
  {
    for (int j = 1; j < B + 1; j++)
    {
      ar[i][j] = rand() % (b_max - a_min + 1) + a_min;
    }
  }

  for (int i = 0; i < A; i++)
  {
    for (int j = 0; j < ar[i][0] + 1; j++)
    {
      printf("%d ", ar[i][j]);
    }
    printf("\n");
  }

  int K;
  printf("Input index element: \n");
  scanf("%d", &K);

  int N;
  printf("Enter the number of numbers you want to add: \n");
  scanf("%d", &N);

  int M;
  printf("Enter the offset for the zeros: \n");
  scanf("%d", &M);

  for (int i = 0; i < A; i++)
  {
    if (i % 4 == 0)
    {
      ar[i] = delete_element(ar[i], K);
    }
    else if (i % 4 == 1)
    {
      ar[i] = append(ar[i], K, N, a_min, b_max);
    }
    else if (i % 4 == 2)
    {
      cyclicShiftZeroes(ar[i], M);
    }
    else
    {
      search(ar[i]);
    }
  }
  printf("The final matrix: \n");
  for (int i = 0; i < A; i++)
  {
    for (int j = 0; j < ar[i][0] + 1; j++)
    {
      if (i == 2){
        if (j == ar[i][0])
        {
          printf("%d\n", ar[i][j]);
        }

        printf("%d ", ar[i][j]);
      }
      
    }
    printf("\n");
  }

  for (int i = 0; i < A; i++)
  {
    free(ar[i]);
  }
  free(ar);

  return 0;
}