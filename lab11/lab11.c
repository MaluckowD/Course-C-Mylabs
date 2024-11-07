#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Vector3d
{
  float x;
  float y;
  float z;
  bool norm;
} Vector3d;

Vector3d create_vector(float x, float y, float z)
{
  float len = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
  bool norm = (len == 1.0f) ? true : false;
  return (Vector3d){x, y, z, norm};
}

Vector3d sum_vectors(const Vector3d *v1, const Vector3d *v2)
{
  return create_vector(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

Vector3d difference_vectors(const Vector3d *v1, const Vector3d *v2)
{
  return create_vector(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}

double angle(const Vector3d *v1, const Vector3d *v2)
{
  float a = (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
  float b = sqrt((pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2)) * (pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2)));
  return acos((float)a / b);
}

Vector3d vector_multiplication(const Vector3d *v1, const Vector3d *v2)
{
  return create_vector((v1->y * v2->z) - (v1->z * v2->y), (v1->z * v2->x) - (v1->x * v2->z), (v1->x * v2->y) - (v1->y * v2->x));
}

Vector3d projection_vector(const Vector3d *v1, const Vector3d *v2)
{
  float scalar = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
  float len = sqrt(pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2));
  float projection_scal = scalar / len;
  return create_vector(projection_scal * v2->x / len, projection_scal * v2->y / len, projection_scal * v2->z / len);
}

void normalization(Vector3d *v)
{
  float len = sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));

  v->x = v->x / len;
  v->y = v->y / len;
  v->z = v->z / len;
  v->norm = true;
}

void print_vector(Vector3d v)
{
  if (v.norm == true)
  {
    printf("(%.2f, %.2f, %.2f) [нормализован]\n", v.x, v.y, v.z);
  }
  else
  {
    printf("(%.2f, %.2f, %.2f) [не нормализован]\n", v.x, v.y, v.z);
  }
}

int main()
{
  Vector3d a1;
  Vector3d a2;
  Vector3d a3;

  printf("Введите координаты вектора a1 (x y z): ");
  scanf("%f %f %f", &a1.x, &a1.y, &a1.z);
  a1 = create_vector(a1.x, a1.y, a1.z);
  print_vector(a1);

  printf("Введите координаты вектора a2 (x y z): ");
  scanf("%f %f %f", &a2.x, &a2.y, &a2.z);
  a2 = create_vector(a2.x, a2.y, a2.z);
  print_vector(a2);

  while (true)
  {
    printf("\nВыберите действие:\n");
    printf("1. Сумма векторов\n");
    printf("2. Разность векторов\n");
    printf("3. Угол между векторами\n");
    printf("4. Векторное произведение\n");
    printf("5. Проекция вектора\n");
    printf("6. Нормализация вектора\n");
    printf("7. Выход\n");
    printf("Введите номер действия: ");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
      printf("Сумма векторов a1 + a2:\n");
      Vector3d sum = sum_vectors(&a1, &a2);
      print_vector(sum);
      break;
    }
    case 2:
    {
      printf("Разность векторов a1 - a2:\n");
      Vector3d diff = difference_vectors(&a1, &a2);
      print_vector(diff);
      break;
    }
    case 3:
    {
      printf("Угол между векторами a1 и a2 (в радианах):\n");
      double angle_rad = angle(&a1, &a2);
      printf("%.2f\n", angle_rad);
      break;
    }
    case 4:
    {
      printf("Векторное произведение векторов a1 и a2:\n");
      Vector3d mult = vector_multiplication(&a1, &a2);
      print_vector(mult);
      break;
    }
    case 5:
    {
      printf("Проекция вектора a1 на a2:\n");
      Vector3d proj = projection_vector(&a1, &a2);
      print_vector(proj);
      break;
    }
    case 6:
    {
      printf("Выберите вектор для нормализации (1 - a1, 2 - a2): ");
      int vector_choice;
      scanf("%d", &vector_choice);

      switch (vector_choice)
      {
      case 1:
        printf("Нормализация вектора a1:\n");
        normalization(&a1);
        print_vector(a1);
        break;
      case 2:
        printf("Нормализация вектора a2:\n");
        normalization(&a2);
        print_vector(a2);
        break;
      default:
        printf("Неверный выбор вектора.\n");
      }
      break;
    }
    case 7:
      printf("Выход из программы.\n");
      return 0;
    default:
      printf("Неверный выбор.\n");
    }
  }

  return 0;
}