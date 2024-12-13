#include "./global.h"



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