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

void normalization(Vector3d *v){
  float len = sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
  
  v->x = v->x / (float)len;
  v->y = v->y / (float)len;
  v->z = v->z / (float)len;
  v->norm = true;
}

void print_vector(Vector3d *v){
  if (v->norm == true){
    printf("(%.2f, %.2f, %.2f) [нормализован]\n", v->x, v->y, v->z);
  }
  else{
    printf("(%.2f, %.2f, %.2f) [не нормализован]\n", v->x, v->y, v->z);
  }
}

int main()
{
  Vector3d a1 = create_vector(2, 2, 2, false);
  Vector3d a2 = create_vector(5, 12, 0, false);
  printf("vector a1:\n");
  print_vector(&a1);
  printf("vector a2:\n");
  print_vector(&a2);
  printf("vector a1 + a2:\n");
  Vector3d sum = sum_vectors(&a1, &a2);
  print_vector(&sum);
  printf("vector a1 - a2:\n");
  Vector3d def = difference_vectors(&a1, &a2);
  print_vector(&def);
  printf("the angle between the vectors in radians:\n");
  double res = angle(&a1, &a2);
  printf("%.2f\n", res);
  printf("vector product:\n");
  Vector3d mult = vector_multiplication(&a1, &a2);
  print_vector(&mult);
  printf("Projection of a vector a1 onto a vector a2:\n");
  Vector3d proj = projection_vector(&a1, &a2);
  print_vector(&proj);
  normalization(&a1);
  printf("The resulting vectors a1 and a2:\n");
  print_vector(&a1);
  print_vector(&a2);
  return 0;
};