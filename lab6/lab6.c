#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define MAX_COORDS 100

// Функция для определения попадания точки в заданную область
int isInArea(float x, float y, float a, float R)
{
  bool a1 = (x >= -a) && (x <= a);
  bool b1 = (y <= 2 * R) && (y >= -2 * R);
  bool c1 = pow(x, 2) + pow((y + 2 * R), 2) >= pow(R, 2);
  bool d1 = pow(x, 2) + pow((y - 2 * R), 2) >= pow(R, 2);
  // printf("%d %d %d %d \n", a1, b1, c1, d1);
  return (a1 && b1 && c1 && d1);
}

void printResults(float (*coords), int N, float R, float a)
{
  printf("Points inside the area:\n");
  for (int i = 0; i < N; i++)
  {
    float x = *(coords + i * 2), y = *(coords + i * 2 + 1);
    // printf("(%.2lf, %.2lf) %.2lf\n", x, y, isInArea(x, y, a, R));
    if (isInArea(x, y, a, R))
    {
      printf("(%.2lf, %.2lf)\n", (*(coords + i * 2)), (*(coords + i * 2 + 1)));
    }
  }

  printf("Points outside the area:\n");
  for (int i = 0; i < N; i++)
  {
    if (!isInArea((*(coords + i * 2)), (*(coords + i * 2 + 1)), a, R))
    {
      printf("(%.2lf, %.2lf)\n", (*(coords + i * 2)), (*(coords + i * 2 + 1)));
    }
  }
}

// Функция для задания массива через random
void randomCoords(int N, float R, float a, float (*coords))
{
  double x_min, x_max, y_min, y_max;
  printf("Enter the minimum value of x: ");
  scanf("%lf", &x_min);
  printf("Enter the maximum value of x: ");
  scanf("%lf", &x_max);
  printf("Enter the minimum value of y: ");
  scanf("%lf", &y_min);
  printf("Enter the maximum value of y: ");
  scanf("%lf", &y_max);
  srand(time(NULL));

  for (int i = 0; i < N; i++)
  {
    (*(coords + i * 2)) = x_min + (float)rand() / RAND_MAX * (x_max - x_min);
    (*(coords + i * 2 + 1)) = y_min + (float)rand() / RAND_MAX * (y_max - y_min);
  }

  for (int i = 0; i < N; i++)
  {
    printf("Point %d: (%.2lf, %.2lf)\n", i + 1, (*(coords + i * 2)), (*(coords + i * 2 + 1)));
  }

  printResults(coords, N, R, a);
}

// Функция для задания массива координат через ввод с клавиатуры
void inputCoords(int N, float R, float a, float (*coords))
{
  for (int i = 0; i < N; i++)
  {
    printf("Input coords %d (x y): ", i + 1);
    scanf("%f %f", &(*(coords + i * 2)), &(*(coords + i * 2 + 1)));
  }

  for (int i = 0; i < N; i++)
  {
    printf("Point %d: (%.2lf, %.2lf)\n", i + 1, (*(coords + i * 2)), (*(coords + i * 2 + 1)));
  }

  printResults(coords, N, R, a);
}

int main()
{
  float R, a;
  printf("Input a, R:\n");
  scanf("%f %f", &a, &R);
  if ((a < 0) || (R < 0))
  {
    printf("Invalid values. Try again");
    return 1;
  }
  int N;
  printf("Input N:\n");
  scanf("%d", &N);
  if (N < 0 || N > MAX_COORDS)
  {
    printf("Invalid value. Try again");
    return 1;
  }

  int choice;
  printf("Choose the way to set the coordinates:\n");
  printf("1. Keyboard input\n");
  printf("2. Randomly\n");
  scanf("%d", &choice);

  float coords[MAX_COORDS * 2];

  void (*funcs)(int, float, float, float(*));
  if (choice == 1)
  {
    funcs = inputCoords;
  }
  else if (choice == 2)
  {
    funcs = randomCoords;
  }
  else
  {
    printf("Wrong choice.\n");
    return 1;
  }
  funcs(N, R, a, (float *)coords);

  return 0;
}
