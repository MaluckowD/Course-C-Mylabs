#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Vector3d
{
  double x;
  double y;
  double z;
  bool norm;
} Vector3d;

Vector3d create_vector(double x, double y, double z, bool norm)
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
  double a = (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
  printf("%lf ", a);
  double b = sqrt((pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2)) * (pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2)));
  printf("%lf ", b);
  return acos((double)a / b);
}

Vector3d vector_multiplication(const Vector3d *v1, const Vector3d *v2)
{
  return (Vector3d){(v1->y * v2->z) - (v1->z * v2->y), (v1->z * v2->x) - (v1->x * v2->z), (v1->x * v2->y) - (v1->y * v2->x)};
}

Vector3d projection_vector(const Vector3d *v1, const Vector3d *v2)
{
  int scalar = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
  double len = sqrt(pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2));
  double projection_scal = (double)scalar / len;
  return (Vector3d){
      projection_scal * v2->x / (double)len,
      projection_scal * v2->y / (double)len,
      projection_scal * v2->z / (double)len,
  };
}

void normalization(Vector3d *v){
  double len = sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
  
  v->x = v->x / (double)len;
  v->y = v->y / (double)len;
  v->z = v->z / (double)len;
  v->norm = true;
}

void print_vector(Vector3d *v){
  if (v->norm == true){
    printf("(%lf, %lf, %lf) [нормализован]\n", v->x, v->y, v->z);
  }
  else{
    printf("(%lf, %lf, %lf) [не нормализован]\n", v->x, v->y, v->z);
  }
}

int main()
{
  Vector3d a1 = create_vector(2, 2, 2, false);
  Vector3d a2 = create_vector(5, 12, 0, false);
  printf("%lf %lf %lf\n", a1.x, a1.y, a1.z);
  printf("%lf %lf %lf\n", a2.x, a2.y, a2.z);
  Vector3d sum = sum_vectors(&a1, &a2);
  printf("%lf %lf %lf\n", sum.x, sum.y, sum.z);
  Vector3d def = difference_vectors(&a1, &a2);
  printf("%lf %lf %lf\n", def.x, def.y, def.z);
  double res = angle(&a1, &a2);
  printf("%lf\n", res);
  Vector3d mult = vector_multiplication(&a1, &a2);
  printf("%lf %lf %lf\n", mult.x, mult.y, mult.z);
  Vector3d proj = projection_vector(&a1, &a2);
  printf("%lf %lf %lf\n", proj.x, proj.y, proj.z);
  normalization(&a1);
  print_vector(&a1);
  print_vector(&a2);
  return 0;
};