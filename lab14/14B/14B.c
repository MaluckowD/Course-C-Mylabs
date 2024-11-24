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
  FILE *fp = fopen("data.txt", "wb");
  if (fp == NULL)
  {
    return 1;
  }

  float x1, y1, z1;
  printf("Введите координаты вектора a1 (x1 y1 z1): ");
  scanf("%f %f %f", &x1, &y1, &z1);
  fwrite(&x1, sizeof(x1), 1, fp);
  fwrite(&y1, sizeof(y1), 1, fp);
  fwrite(&z1, sizeof(z1), 1, fp);

  float x2, y2, z2;
  printf("Введите координаты вектора a2 (x2 y2 z2): ");
  scanf("%f %f %f", &x2, &y2, &z2);
  fwrite(&x2, sizeof(x2), 1, fp);
  fwrite(&y2, sizeof(y2), 1, fp);
  fwrite(&z2, sizeof(z2), 1, fp);

  printf("\nВыберите действие:\n");
  printf("1. Сумма векторов\n");
  printf("2. Разность векторов\n");
  printf("3. Угол между векторами\n");
  printf("4. Векторное произведение\n");
  printf("5. Проекция вектора\n");
  printf("6. Нормализация вектора\n");
  printf("Введите номера действий: \n");

  int count = 0;
  int ar[20];

  while (scanf("%d", &ar[count]) == 1)
  {
    count++;
    if (count >= 20)
    {
      break;
    }
    if (getchar() == '\n')
    {
      break;
    }
  }

  for (int i = 0; i < count; i++)
  {
    fwrite(&ar[i], sizeof(ar[i]), 1, fp);
  }

  fclose(fp);

  FILE *fr = fopen("data.txt", "rb");
  if (fr == NULL)
  {
    return 1;
  }

  float x11, y12, z13;
  float x21, y22, z23;

  fread(&x11, sizeof(x11), 1, fr);
  fread(&y12, sizeof(y12), 1, fr);
  fread(&z13, sizeof(z13), 1, fr);

  fread(&x21, sizeof(x21), 1, fr);
  fread(&y22, sizeof(y22), 1, fr);
  fread(&z23, sizeof(z23), 1, fr);

  fclose(fr);

  Vector3d a1 = create_vector(x11, y12, z13);
  Vector3d a2 = create_vector(x21, y22, z23);

  FILE *ft = fopen("result.txt", "wb");
  if (ft == NULL)
  {
    return 1;
  }

  for (int i = 0; i < count; i++)
  {
    switch (ar[i])
    {
    case 1:
    {
      Vector3d sum = sum_vectors(&a1, &a2);
      fwrite(&ar[i], sizeof(int), 1, ft);
      fwrite(&a1, sizeof(Vector3d), 1, ft);
      fwrite(&a2, sizeof(Vector3d), 1, ft);
      fwrite(&sum, sizeof(Vector3d), 1, ft);
      break;
    }
    case 2:
    {
      Vector3d diff = difference_vectors(&a1, &a2);
      fwrite(&ar[i], sizeof(int), 1, ft);
      fwrite(&a1, sizeof(Vector3d), 1, ft);
      fwrite(&a2, sizeof(Vector3d), 1, ft);
      fwrite(&diff, sizeof(Vector3d), 1, ft);
      break;
    }
    case 3:
    {
      double angle_rad = angle(&a1, &a2);
      fwrite(&ar[i], sizeof(int), 1, ft);
      fwrite(&a1, sizeof(Vector3d), 1, ft);
      fwrite(&a2, sizeof(Vector3d), 1, ft);
      fwrite(&angle_rad, sizeof(double), 1, ft);
      break;
    }
    case 4:
    {
      Vector3d mult = vector_multiplication(&a1, &a2);
      fwrite(&ar[i], sizeof(int), 1, ft);
      fwrite(&a1, sizeof(Vector3d), 1, ft);
      fwrite(&a2, sizeof(Vector3d), 1, ft);
      fwrite(&mult, sizeof(Vector3d), 1, ft);
      break;
    }
    case 5:
    {
      Vector3d proj = projection_vector(&a1, &a2);
      fwrite(&ar[i], sizeof(int), 1, ft);
      fwrite(&a1, sizeof(Vector3d), 1, ft);
      fwrite(&a2, sizeof(Vector3d), 1, ft);
      fwrite(&proj, sizeof(Vector3d), 1, ft);
      break;
    }
    case 6:
    {
      int vector_choice;
      printf("Выберите вектор для нормализации (1 - a1, 2 - a2): ");
      scanf("%d", &vector_choice);
      if (vector_choice == 1)
      {
        normalization(&a1);
        fwrite(&ar[i], sizeof(int), 1, ft);
        fwrite(&a1, sizeof(Vector3d), 1, ft);
        fwrite(&a2, sizeof(Vector3d), 1, ft);
        fwrite(&a1, sizeof(Vector3d), 1, ft);
      }
      else if (vector_choice == 2)
      {
        normalization(&a2);
        fwrite(&ar[i], sizeof(int), 1, ft);
        fwrite(&a1, sizeof(Vector3d), 1, ft);
        fwrite(&a2, sizeof(Vector3d), 1, ft);
        fwrite(&a2, sizeof(Vector3d), 1, ft);
      }
      else
      {
        printf("Неверный выбор вектора.\n");
      }
      break;
    }
    default:
      printf("Неверный выбор.\n");
    }
  }

  fclose(ft);

  FILE *fr_result = fopen("result.txt", "rb");
  if (fr_result == NULL)
  {
    return 1;
  }

  int operation;
  Vector3d a, b, result;
  double angle_rad;

  while (fread(&operation, sizeof(int), 1, fr_result) == 1)
  {
    fread(&a, sizeof(Vector3d), 1, fr_result);
    fread(&b, sizeof(Vector3d), 1, fr_result);

    switch (operation)
    {
    case 1:
      fread(&result, sizeof(Vector3d), 1, fr_result);
      printf("Сумма векторов a1 + a2:\n");
      print_vector(result);
      break;
    case 2: 
      fread(&result, sizeof(Vector3d), 1, fr_result);
      printf("Разность векторов a1 - a2:\n");
      print_vector(result);
      break;
    case 3: 
      fread(&angle_rad, sizeof(double), 1, fr_result);
      printf("Угол между векторами a1 и a2 (в радианах): %.2f\n", angle_rad);
      break;
    case 4: 
      fread(&result, sizeof(Vector3d), 1, fr_result);
      printf("Векторное произведение векторов a1 и a2:\n");
      print_vector(result);
      break;
    case 5: 
      fread(&result, sizeof(Vector3d), 1, fr_result);
      printf("Проекция вектора a1 на a2:\n");
      print_vector(result);
      break;
    case 6: 
      fread(&result, sizeof(Vector3d), 1, fr_result);
      printf("Нормализованный вектор:\n");
      print_vector(result);
      break;
    default:
      printf("Неверный выбор операции.\n");
    }
  }

  fclose(fr_result);
  return 0;
}
