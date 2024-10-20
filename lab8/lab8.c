#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

void *delete_element(int *data, int K){

  if ((K > data[0]) || (K <= 0)){
    return data;
  }
  //printf("%d ", data[0]);
  int *arr = malloc(sizeof(int) * (data[0]));
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
  if ((K > data[0]) || (K <= 0))
  {
    return data;
  }

  int *arr = malloc(sizeof(int) * (N + data[0] + 1));
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
  int K;
  printf("Input index element you want delete: \n");
  scanf("%d", &K);

  coords[0] = delete_element(coords[0], K);
  coords[1] = search(coords[1]);
  coords[2] = append(coords[2], 4, 2,  a_min, b_max);
  for (int i = 0; i <= coords[0][0]; i++)
  {
    printf("%d  ", coords[0][i]);
  }
  for (int i = 0; i <= coords[1][0]; i ++){
    printf("%d ", coords[1][i]);
  }
  for (int i = 0; i <= coords[2][0]; i++)
  {
    printf("%d ", coords[2][i]);
  }

  // Освобождение выделенной памяти
  for (int i = 0; i < A; i++)
  {
    free(coords[i]);
  }
  free(coords);

  return 0;
}