#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char str[1000];
  strcpy(str, argv[1]);
  int count = 0;
  char *pt = str;
  char *ptr = strpbrk(str, "!?.");
  // printf("%p %p", str, ptr);
  if (ptr != pt)
  {
    count++;
  }
  ptr++;
  pt = ptr;

  while (pt != NULL)
  {
    ptr = strpbrk(str, "!?.");
    if (pt == ptr)
    {
      ptr++;
      pt = ptr;
      continue;
    }
    count++;
    ptr++;
    pt = ptr;
  }

  printf("%d\n", count);
  puts(str);

  return 0;
}