#include <stdio.h>
#include <math.h>

int main()
{
  double a;
  printf("Input a value: \n");
  scanf("%lf", &a);

  int nm1, nm2;
  printf("Input nm1, nm2 values: \n");
  scanf("%d %d", &nm1, &nm2);

  if ((nm1 < 2) || (nm1 > 6) || (nm2 < 2) || (nm2 > 6))
  {
    printf("Input correct nm1 or nm2");
    return 0;
  }

  double x0, y0;
  double xh, xn;
  printf("Input x0, xh, xn values: \n");
  scanf("%lf %lf %lf", &x0, &xh, &xn);

  double yh, yn;
  printf("Input y0, yh, yn values: \n");
  scanf("%lf %lf %lf", &y0, &yh, &yn);

  double mx = -1E6;
  double mn = 1E6;

  printf("+--------+--------+--------+\n");
  printf("| %-6s | %-6s | %-5s |\n", "x", "y", "f(x,y)");
  printf("+--------+--------+--------+\n");
  for (double y = y0; y <= yn; y += yh)
  {
    for (double x = x0; x <= xn; x += xh)
    {
      double z = 0;
      int flag = 0;

      if (x <= a * y)
      {
        for (int n = 1; n <= nm1; n++)
        {
          z += (double)(y * n + x) / (n * pow(x, n + 1) + 1);
        }
      }
      else
      {
        for (int n = 0; n <= nm2; n++)
        {
          if (n + y <= 0)
          {
            flag = 1;
            break;
          }
          z += (double)(x - y) / (pow(n + y, 0.5));
        }
      }
      if (z > mx)
      {
        mx = z;
      }
      if (z < mn)
      {
        mn = z;
      }

      if (flag == 0){
        printf("|%-8.3f|%-8.3f|%-8.3f|\n", x, y, z);
        printf("+--------+--------+--------+\n");
      }
      
    }
  }

  printf("min = %.3f; max = %.3f\n", mn, mx);
  return 0;
}
