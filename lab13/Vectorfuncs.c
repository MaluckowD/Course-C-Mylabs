#include "./global.h"

Vector3d create_vector(float x, float y, float z, bool norm)
{

  return (Vector3d){x, y, z, norm};
}

Vector3d sum_vectors(const Vector3d *v1, const Vector3d *v2)
{
  return (Vector3d){v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
}

Vector3d difference_vectors(const Vector3d *v1, const Vector3d *v2)
{
  return (Vector3d){v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
}

double angle(const Vector3d *v1, const Vector3d *v2)
{
  float a = (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
  float b = sqrt((pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2)) * (pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2)));
  return acos((float)a / b);
}

Vector3d vector_multiplication(const Vector3d *v1, const Vector3d *v2)
{
  return (Vector3d){(v1->y * v2->z) - (v1->z * v2->y), (v1->z * v2->x) - (v1->x * v2->z), (v1->x * v2->y) - (v1->y * v2->x)};
}

Vector3d projection_vector(const Vector3d *v1, const Vector3d *v2)
{
  int scalar = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
  printf("Скалярное произведение: %d\n", scalar);
  float len = sqrt(pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2));
  printf("Длина вектора a2: %.2f\n", len);
  float projection_scal = (float)scalar / len;
  printf("Длина проекции a1 на a2: %.2f\n", projection_scal);
  return (Vector3d){
      projection_scal * v2->x / (float)len,
      projection_scal * v2->y / (float)len,
      projection_scal * v2->z / (float)len,
  };
}

void normalization(Vector3d *v)
{
  float len = sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));

  v->x = v->x / (float)len;
  v->y = v->y / (float)len;
  v->z = v->z / (float)len;
  v->norm = true;
}

void print_vector(Vector3d *v)
{
  if (v->norm == true)
  {
    printf("(%.2f, %.2f, %.2f) [нормализован]\n", v->x, v->y, v->z);
  }
  else
  {
    printf("(%.2f, %.2f, %.2f) [не нормализован]\n", v->x, v->y, v->z);
  }
}