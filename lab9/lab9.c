#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
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

void create()
{
  // Реализуйте функцию create()
}

int main(int argc, char *argv[])
{
  char str[1000];
  strcpy(str, argv[1]);
  int count = info_count(str); // Количество слов

  // Выделение памяти для массива указателей на строки
  char **ar = (char **)malloc(count * sizeof(char *));
  if (ar == NULL)
  {
    return 1; // Обработка ошибки: не удалось выделить память
  }

  // Выделение памяти для каждой строки
  for (int i = 0; i < count; i++)
  {
    ar[i] = (char *)malloc(100 * sizeof(char));
    if (ar[i] == NULL)
    {
      return 1; // Обработка ошибки: не удалось выделить память
    }
  }

  const char delimiters[] = ",.!? ";
  const char glas[] = "йцкнгшщзхфвпрлджчсмтб";
  const char sogl[] = "уеыаоэюия";
  char *token = strtok(str, delimiters);

  int c = 0; // Счетчик для массива ar
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

  printf("%d\n", count); // Вывод количества слов

  // Вывод слов, в которых согласных больше, чем гласных
  for (int i = 0; i < c; i++)
  {
    puts(ar[i]);
  }

  // Освобождение памяти
  for (int i = 0; i < count; i++)
  {
    free(ar[i]);
  }
  free(ar);

  return 0;
}