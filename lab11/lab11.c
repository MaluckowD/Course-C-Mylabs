#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Vector3d{
  double x;
  double y;
  double z;
} Vector3d;

Vector3d create_vector(double x, double y, double z){

  return (Vector3d){x, y, z};
}

Vector3d sum_vectors(const Vector3d *v1, const Vector3d *v2){
  return (Vector3d) { v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
}

Vector3d difference_vectors(const Vector3d *v1, const Vector3d *v2)
{
  return (Vector3d) { v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
}

double angle()

int main(){
  Vector3d a1 = create_vector(1, 2, 3);
  Vector3d a2 = create_vector(4, 3, 3);
  printf("%lf %lf %lf\n", a1.x, a1.y, a1.z);
  printf("%lf %lf %lf\n", a2.x, a2.y, a2.z);
  Vector3d sum = sum_vectors(&a1, &a2);
  printf("%lf %lf %lf\n", sum.x, sum.y, sum.z);
  Vector3d def = difference_vectors(&a1, &a2);
  printf("%lf %lf %lf\n", def.x, def.y, def.z);

  return 0;
};