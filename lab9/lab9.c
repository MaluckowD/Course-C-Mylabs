#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

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
  char *ar = malloc(100 * sizeof(char));
  
  const char delimiters[] = ",.!? ";
  const char glas[] = "йцкнгшщзхфвпрлджчсмтб";
  const char sogl[] = "уеыаоэюия";
  char *token = strtok(str, delimiters);

  while (token != NULL)
  {
    //printf("Token: %s\n", token);
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < strlen(token); i++){
      if (strchr(glas, token[i]) != NULL)
      {
        count1++;
      }
      if (strchr(sogl, token[i]) != NULL)
      {
        count2++;
      }
        }
    if (count2 > count1){
      printf("%s\n", token);
    }
    
    token = strtok(NULL, delimiters);
  }

  printf("%d\n", count);
  
  return 0;
}