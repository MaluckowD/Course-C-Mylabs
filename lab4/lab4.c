#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define MAX_COORDS 100 // Максимальное количество координат

// Функция для определения попадания точки в заданную область
int isInArea(double x, double y, double a, double R)
{
  bool a1 = (x >= -a) && (x <= a);
  bool b1 = (y <= 2 * R) && (y >= -2 * R);
  bool c1 = pow(x, 2) + pow((y + 2 * R), 2) >= pow(R, 2);
  bool d1 = pow(x, 2) + pow((y - 2 * R), 2) >= pow(R, 2);
  return (a1 && b1 && c1 && d1);
}

void printResults(double coords[][2], int N, double R, double a)
{
  printf("Points inside the area:\n");
  for (int i = 0; i < N; i++)
  {
    if (isInArea(coords[i][0], coords[i][1], a, R))
    {
      printf("(%.2lf, %.2lf)\n", coords[i][0], coords[i][1]);
    }
  }

  printf("Points outside the area:\n");
  for (int i = 0; i < N; i++)
  {
    if (!isInArea(coords[i][0], coords[i][1], a, R))
    {
      printf("(%.2lf, %.2lf)\n", coords[i][0], coords[i][1]);
    }
  }
}

// Функция для задания массива через random
void randomCoords(int N, double x_min, double x_max, double y_min, double y_max, double R, double a, double coords[][2])
{
  srand(time(NULL));
  for (int i = 0; i < N; i++)
  {
    coords[i][0] = x_min + (double)rand() / RAND_MAX * (x_max - x_min);
    coords[i][1] = y_min + (double)rand() / RAND_MAX * (y_max - y_min);
  }

  for (int i = 0; i < N; i++)
  {
    printf("Point %d: (%.2lf, %.2lf)\n", i + 1, coords[i][0], coords[i][1]);
  }

  printResults(coords, N, R, a);
}

// Функция для задания массива координат через ввод с клавиатуры
void inputCoords(int N, double R, double a, double coords[][2])
{
  for (int i = 0; i < N; i++)
  {
    printf("Input coords %d (x y): ", i + 1);
    scanf("%lf %lf", &coords[i][0], &coords[i][1]);
  }

  for (int i = 0; i < N; i++)
  {
    printf("Point %d: (%.2lf, %.2lf)\n", i + 1, coords[i][0], coords[i][1]);
  }

  printResults(coords, N, R, a);
}

int main()
{
  double R, a;
  printf("Input a, R:\n");
  scanf("%lf %lf", &a, &R);
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
  double x_min, x_max, y_min, y_max;

  double coords[MAX_COORDS][2]; // Статический массив

  if (choice == 1)
  {
    inputCoords(N, R, a, coords);
  }
  else if (choice == 2)
  {
    printf("Enter the minimum value of x: ");
    scanf("%lf", &x_min);
    printf("Enter the maximum value of x: ");
    scanf("%lf", &x_max);
    printf("Enter the minimum value of y: ");
    scanf("%lf", &y_min);
    printf("Enter the maximum value of y: ");
    scanf("%lf", &y_max);
    randomCoords(N, x_min, x_max, y_min, y_max, R, a, coords);
  }
  else
  {
    printf("Wrong choice.\n");
    return 1;
  }

  return 0;
}