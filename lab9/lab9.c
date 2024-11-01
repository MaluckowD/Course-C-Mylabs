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

void create(char *str, char **ar)
{
  const char delimiters[] = ",.!? ";
  const char glas[] = "йцкнгшщзхфвпрлджчсмтбЙЦКНГШЩЗХФВПРЛДЖЧСМТБqwrtpsdfghklzxcvbnmQWRTPSDFGHKLZXCVBBNM";
  const char sogl[] = "уеыаоэюияУЕЫАОЭЯЮeyuioajEYUIOAJ";
  char *token = strtok(str, delimiters);
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

void remove_trailing_numbers(char *text)
{
  int len = strlen(text);
  int i = len - 1;
  bool in_sentence = true;

  while (i >= 0)
  {
    if (text[i] == '!' || text[i] == '?' || text[i] == '.')
    {
      in_sentence = true;
    }
    else if (isdigit(text[i]))
    {
      if (in_sentence)
      {
        for (int j = i; text[j] != '\0'; j++)
        {
          text[j] = text[j + 1];
        }

        while (i >= 0 && (isdigit(text[i]) || text[i] == ' '))
        { 
          
          for (int j = i; text[j] != '\0'; j++)
          {
            text[j] = text[j + 1];
          }
          i--;
        }
      }
    }
    else if (text[i] != ' ')
    { 
      in_sentence = false;
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

  char choice[10];
  strcpy(choice, argv[2]);

  if (strcmp (choice, "-info") == 0){
    int count = info_count(str);

    printf("There are %d sentences in the text\n", count);
  }
  else if (strcmp(choice, "-create") == 0){
    printf("Words with a lot of consonants: \n");
    char **ar = (char **)malloc(100 * sizeof(char *));
    if (ar == NULL)
    {
      return 1;
    }

    for (int i = 0; i < 1000; i++)
    {
      ar[i] = (char *)malloc(1000 * sizeof(char));
      if (ar[i] == NULL)
      {
        return 1;
      }
    }
    create(str, ar);
    for (int i = 0; i < 1000; i++)
    {
      free(ar[i]);
    }
    free(ar);

  }
  else if (strcmp(choice, "-delete") == 0){
    puts(str1);
    remove_trailing_numbers(str1);
    puts(str1);
  }
  else{
    printf("Input correct arguments");
  }

  return 0;
}