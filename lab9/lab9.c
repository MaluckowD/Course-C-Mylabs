#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int info_count(char str[])
{
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

void *create(char *str, char **ar)
{
  const char delimiters[] = ",.!? ";
  const char glas[] = "йцкнгшщзхфвпрлджчсмтб";
  const char sogl[] = "уеыаоэюия";
  char *token = strtok(str, delimiters);
  const char num[] = "0123456789";
  int c = 0;
  while (token != NULL)
  {
    int count1 = 0;
    int count2 = 0;

    for (int i = 0; i < strlen(token); i++)
    {
      if (strchr(glas, token[i]) != NULL)
      {
        count1++;
      }
      if (strchr(sogl, token[i]) != NULL)
      {
        count2++;
      }
    }
    if (count2 > count1)
    {
      strcpy(ar[c], token);
      c++;
    }

    token = strtok(NULL, delimiters);
  }

  for (int i = 0; i < c; i++)
  {
    puts(ar[i]);
  }
}

void *remove_trailing_numbers(char *text)
{
  int len = strlen(text);
  int i = len - 1;

  // Проходим по строке справа налево
  while (i >= 0)
  {
    // Если нашли пунктуационный знак
    if (text[i] == '!' || text[i] == '?' || text[i] == '.')
    {
      // Удаляем цифры до начала предложения
      while (i >= 0 && isdigit(text[i]))
      {
        text[i] = '\0';
        i--;
      }
    }
    i--;
  }
}

int main(int argc, char *argv[])
{
  char str[1000];
  strcpy(str, argv[1]);
  char str1[1000];
  strcpy(str1, argv[1]);
  int count = info_count(str); 

  char **ar = (char **)malloc(count * sizeof(char *));
  if (ar == NULL)
  {
    return 1;
  }

  for (int i = 0; i < count; i++)
  {
    ar[i] = (char *)malloc(100 * sizeof(char));
    if (ar[i] == NULL)
    {
      return 1; 
    }
  }

  create(str, ar);
  printf("%d\n", count);
  puts(str1);
  remove_trailing_numbers(str1);
  puts(str1);

  for (int i = 0; i < count; i++)
  {
    free(ar[i]);
  }
  free(ar);

  return 0;
}