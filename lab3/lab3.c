
#include <stdio.h>
#include <math.h>
#include <float.h>

int main()
{
  float a;
  printf("Input a value: \n");
  scanf("%f", &a); 

  int nm1, nm2;
  printf("Input nm1, nm2 values in [2,6]: \n");
  scanf("%d %d", &nm1, &nm2); 

  if ((nm1 < 2) || (nm1 > 6) || (nm2 < 2) || (nm2 > 6))
  {
    printf("Input correct nm1 or nm2");
    return 0;
  }

  float x0, y0;
  float xh, xn;
  float argx, argy, argx1, argy1;
  printf("Input x0, xh, xn values: \n");
  scanf("%f %f %f", &x0, &xh, &xn);
  if ((xh > 0) && (xn > x0)){
    printf("Errow\n");
    return 1;
  }
  
  float yh, yn;
  printf("Input y0, yh, yn values: \n");
  scanf("%f %f %f", &y0, &yh, &yn);
  if ((yh > 0) && (yn > y0))
  {
    printf("Errow\n");
    return 1;
  }

  float mx = -FLT_MAX;
  float mn = FLT_MAX;
 
  printf("+--------+--------+--------+\n");
  printf("| %-6s | %-6s | %-5s |\n", "x", "y","f(x,y)");
  printf("+--------+--------+--------+\n");
  for (float y = y0; y <= yn; y += yh){
    int flag = 0;
    for (float x = x0; x <= xn; x += xh){
      float z = 0;

      if (x <= a * y)
      {
        for (int n = 1; n <= nm1; n++)
        {
          z += (float)(y * n + x) / (n * pow(x, n + 1) + 1);
        }
      }
      else
      {
        for (int n = 0; n <= nm2; n++)
        {
          if (n + y <= 0)
          {
            flag = 1;
            continue;
          }
          z += (float)(x - y) / (pow(n + y, 0.5));
        }
      }
      if (z > mx)
      {
        mx = z;
        argx = x;
        argy = y;
      }
      if (z < mn)
      {
        mn = z;
        argx1 = x;
        argy1 = y;
      }
      
      if (z != 0){
        printf("|%-4f|%-4f|%-8.3f|\n", x, y, z);
        printf("+--------+--------+--------+\n");
      }
    }

  }

  printf("min(%.3f %.3f) = %.3f max(%.3f %.3f) = %.3f", argx1, argy1, mn, argx, argy, mx);
  return 0;
}
