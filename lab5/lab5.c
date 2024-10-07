#include <stdio.h>

#define MAX_LEN 100 

void elemInArrayIteration(float massive[], int N, float elem){
  for (int i = 0; i < N; i++){
    if (massive[i] == elem){
      printf("The element is included in the array calculated by iterations\n");
      return;
    }
  }
  printf("The element is not included in the array calculated by iterations\n");
  return;
}

void elemInArrayRecursion(float massive[], int i, int N, float elem){
  if (massive[i] == elem){
    printf("The element is included in the array calculated by recursion\n");
    return;
  }
  if (i == N - 1)
  {
    printf("The element is not included in the array calculated by recursion\n");
    return;
  }
  i++;
  elemInArrayRecursion(massive, i, N, elem);

}

int main()
{

  int N;
  printf("Input N:\n");
  scanf("%d", &N);
  if (N <= 0 || N > MAX_LEN)
  {
    printf("Invalid value. Try again");
    return 1;
  }
  float element;
  printf("Input your element: \n");
  scanf("%f", &element);

  printf("Enter the array elements: \n");
  float massive[MAX_LEN];
  int count = 0;
  while ((count < N)){
    scanf("%f", &massive[count]);
    count++;
  }
  printf("You have entered the following array: \n");
  for (int i = 0; i < count; i++){
    if (i == count - 1){
      printf("%.3f\n", massive[i]);
      break;
    }
    printf("%.3f ",massive[i]);
  }

  elemInArrayIteration(massive, N, element);
  elemInArrayRecursion(massive, 0, N, element);

  return 0;
}