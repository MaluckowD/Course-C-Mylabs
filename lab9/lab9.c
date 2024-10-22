#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int info_count(char str[]){
  int count = 0;
  char *pt = str;
  char *ptr = strpbrk(str, "!?.");

  if (ptr != pt)
  {
    count++;
  }

  ptr++;
  pt = ptr;

  while (ptr != NULL)
  {
    ptr = strpbrk(pt, "!?.`\0`");

    if (pt == ptr)
    {
      ptr++;
      pt = ptr;
      continue;
    }
    if (ptr == NULL)
    {
      break;
    }
    count++;

    ptr++;
    pt = ptr;
  }

  int n = strlen(str);
  if ((str[n - 1] != '!' && str[n - 1] != '?' && str[n - 1] != '.') && (str[n] == '\0'))
  {

    count++;
  }
  return count;
}

int main(int argc, char *argv[])
{
  char str[1000];
  strcpy(str, argv[1]);
  int count = info_count(str);

  printf("%d\n", count);
  

  return 0;
}