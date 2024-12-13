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

  while (ptr != NULL){
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

void create(char *str, char ***ar, int *count)
{

  const char delimiters[] = ",.!? ";
  const char glas[] = "йцкнгшщзхфвпрлджчсмтбЙЦКНГШЩЗХФВПРЛДЖЧСМТБqwrtpsdfghjklzxcvbnmQWRTPSDFGHJKLZXCVBNM";
  const char sogl[] = "уеыаоэюияУЕЫАОЭЯЮeyuioajEYUIOAJ";

  char *copy = (char *)malloc(strlen(str) + 1);
  if (copy == NULL)
  {
    perror("Malloc failed!");
    exit(1);
  }
  strcpy(copy, str);

  char *token = strtok(copy, delimiters);
  *count = 0;

  while (token != NULL)
  {
    int count1 = 0;
    int count2 = 0;

    for (int i = 0; token[i] != '\0'; i++)
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
      (*ar)[*count] = (char *)malloc((strlen(token) + 1) * sizeof(char));
      if ((*ar)[*count] == NULL)
      {
        perror("Memory allocation failed");
        exit(1);
      }
      strcpy((*ar)[*count], token);
      (*count)++;
    }

    token = strtok(NULL, delimiters);
  }
  free(copy);
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

void solve(char choice[], char str[], FILE *out)
{

  if (strcmp(choice, "info") == 0)
  {
    int count = info_count(str);

    fprintf(out,"There are %d sentences in the text\n", count);
  }
  else if (strcmp(choice, "create") == 0)
  {
    fprintf(out, "Words with a lot of consonants: \n");
    int count = 0;                                     
    char **ar = (char **)malloc(100 * sizeof(char *));

    if (ar == NULL)
    {
      return;
    }

    create(str, &ar, &count); 
    for (int i = 0; i < count; i++){ 
      fputs(ar[i], out);
      fputc('\n', out);
      free(ar[i]);
    }
    free(ar);
  }
  else if (strcmp(choice, "delete") == 0)
  {
    fprintf(out,"Текст до удаления:\n");
    fputs(str, out);
    fputc('\n', out);
    remove_trailing_numbers(str);
    fprintf(out,"Текст после удаления:\n");
    fputs(str, out);
    fputc('\n', out);
  }
  else
  {
    printf("Input correct arguments");
  }
}

int main(int argc, char *argv[])
{

  char data[1000];
  strcpy(data, argv[1]);

  char buffer[1000];

  FILE *in = fopen(data, "r");
  if (in == NULL){
    return 1;
  }

  char result[100];
  strcpy(result, argv[2]);
  FILE *out = fopen(result, "w");
  if (in == NULL)
  {
    return 1;
  }

  char string[20][300];
  int i = 0;
  int line_count = 0;
  while (fgets(buffer, sizeof(buffer), in) != NULL)
  {
    line_count++;
  }

  rewind(in);
  while (fgets(buffer, sizeof(buffer), in) && (i < 20)){
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(string[i], buffer);
    i++;  
  }

  fclose(in);
  char *token;
  char *search = "\"";
  for (int i = 0; i < line_count; i++)
  {
    char *p = strstr(string[i], " -");
    *p = '\0';
    solve(p + strlen(" -"), string[i], out);
  }

  printf("В файл были успешно добавлены данные\n");
  fclose(out);
  return 0;
}