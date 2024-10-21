#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define DEFAULT_VALUE 100000

void *delete_element(int *data, int K){

  if ((K > data[0]) || (K <= 0)){
    return data;
  }

  int *arr = malloc(sizeof(int) * (data[0]));
  if (arr == NULL){
    return data;
  }
  int count = 1;
  for (int i = 1; i < K; i++){
    arr[count++] = data[i];
  }
  for (int i = K + 1; i <= data[0]; i++)
  {
    arr[count++] = data[i];
  }
  arr[0] = --data[0];
  free(data);
  data = arr;
  return data;
}

void *search(int *data){
  for (int i = 1; i < data[0]; i++){
    if (data[i] % 2 == 0){
      data[i] = 0;
      return data;
    }
  }
  return data;
}

void *append(int *data, int K, int N, int a_min, int b_max){
  srand(time(NULL));
  if ((K > data[0]) || (K <= 0) || N <= 0)
  {
    return data;
  }

  int *arr = malloc(sizeof(int) * (N + data[0] + 1));
  if (arr == NULL)
  {
    return data;
  }
  int count = 1;
  for (int i = 1; i < K; i++ ){
    arr[count++] = data[i];
  }

  for (int i = 0; i < N; i++){
    arr[count++] = rand() % (b_max - a_min + 1) + a_min;
  }

  for (int i = K; i <= data[0]; i++){
   arr[count++] = data[i];
  }

  arr[0] = data[0] + N;
  free(data);
  data = arr;
  return data;
}

void *cyclicShiftZeroes(int *line, int m)
{

  if (m < 0)
  {
    printf("M must be >= 0\n");
    exit(1);
  }

  int n = line[0];

  int *zeroes = (int *)malloc(n * sizeof(int));
  if (zeroes == NULL)
  {
    printf("Segmentation error!\n");
    exit(1);
  }

  int zeroes_counter = 0;

  for (int i = 1; i <= n; ++i)
    if (line[i] == 0)
      zeroes[zeroes_counter++] = (i - 1 - m + n) % n + 1;

  int *new_line = (int *)malloc((n + 1) * sizeof(int));
  if (new_line == NULL)
  {
    printf("Segmentation error!\n");
    exit(1);
  }
  new_line[0] = line[0];

  for (int i = 1; i <= n; ++i)
    new_line[i] = DEFAULT_VALUE;

  for (int i = 0; i < zeroes_counter; ++i)
    new_line[zeroes[i]] = 0;

  int ptr = 1;
  for (int i = 1; i <= n; ++i)
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

int main()
{

  int A, B;
  printf("Input A, B: \n");
  scanf("%d %d", &A, &B);
  if ((A < 0) && (B < 0)){
    printf("Input correct A and B\n");
    return 0;
  }
  int a_min, b_max;
  printf("Input Enter the left and right generation range: \n");
  scanf("%d %d", &a_min, &b_max);
  if (a_min >= b_max){
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
    ar[i] = (int *)malloc((B + 1)  * sizeof(int));
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

  for (int i = 0; i < A; i++){
    if (i % 4 == 0){
      ar[i] = delete_element(ar[i], K);
    }
    else if( i % 4 == 1){
      ar[i] = append(ar[i], K, N, a_min, b_max);
    }
    else if (i % 4 == 2){
      ar[i] = cyclicShiftZeroes(ar[i], M);
    }
    else{
      ar[i] = search(ar[i]);
    }
  }
  printf("The final matrix: \n");
  for (int i = 0; i < A; i++)
  {
    for (int j = 0; j < ar[i][0] + 1; j++)
    {
      if (j == ar[i][0]){
        printf("%d\n", ar[i][j]);
        break;
      }

      printf("%d ", ar[i][j]);
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