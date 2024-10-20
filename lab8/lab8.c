#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

void *delete_element(int *data, int K){

  if ((K > data[0]) || (K <= 0)){
    return data;
  }

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
  if ((K > data[0]) || (K <= 0) || N <= 0)
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

void *cyclic_shift_element_left(int *data, int M)
{
  if (M < 0){
    return data;
  }
  int *arr = malloc(sizeof(int) * (data[0] + 1)); // Выделяем память для нового массива
  arr[0] = data[0];                               // Сохраняем размер массива
  int count = 1;                                  // Индекс для заполнения нового массива

  for (int i = 1; i <= data[0]; i++)
  {
    if (data[i] == 0)
    {
      int new_index = (i - M + data[0]) % data[0]; // good

      // Сдвиг влево
      if (i > new_index)
      {
        for (int j = i; j > new_index; j--)
        {
          arr[count++] = data[j - 1];
        }
      }
      else if (i < new_index)
      {
        for (int j = i + 1; j <= data[0]; j++)
        {
          arr[count++] = data[j];
        }
        for (int j = 1; j <= new_index; j++)
        {
          arr[count++] = data[j];
        }
      }
      else
      {
        arr[count++] = data[i]; //  i == new_index
      }
      arr[count++] = 0; // Добавляем ноль на новое место
    }
    else
    {
      arr[count++] = data[i]; //  i == new_index
    }
  }

  free(data);
  data = arr; // Переназначаем указатель data на arr

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
    for (int j = 0; j < coords[i][0] + 1; j++)
    {
      printf("%d ", coords[i][j]); 
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
      coords[i] = delete_element(coords[i], K);
    }
    else if( i % 4 == 1){
      coords[i] = append(coords[i], K, N, a_min, b_max);
    }
    else if (i % 4 == 2){
      coords[i] = cyclic_shift_element_left(coords[i], -10);
    }
    else{
      coords[i] = search(coords[i]);
    }
  }
  //int K;
  //printf("Input index element you want delete: \n");
  //scanf("%d", &K);
  //coords[0] = delete_element(coords[0], K);
  //coords[1] = search(coords[1]);
  //coords[2] = append(coords[2], 4, 2,  a_min, b_max);
  //coords[3] = cyclic_shift_element_left(coords[3], 2);
  for (int i = 0; i < A; i++)
  {
    for (int j = 0; j < coords[i][0] + 1; j++)
    {
      if (j == coords[i][0]){
        printf("%d\n", coords[i][j]);
        break;
      }

      printf("%d ", coords[i][j]);
    }
    printf("\n");
  }

  // Освобождение выделенной памяти
  for (int i = 0; i < A; i++)
  {
    free(coords[i]);
  }
  free(coords);

  return 0;
}