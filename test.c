#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>

#define MAX_SENTENCES 100
#define MAX_LENGTH 256
#define MAX_SENTENCE_LEN 1024

// Р¤СѓРЅРєС†РёСЏ РґР»СЏ РїРѕРґСЃС‡РµС‚Р° РєРѕР»РёС‡РµСЃС‚РІР° РіР»Р°СЃРЅС‹С… РІ С‚РµРєСЃС‚Рµ
int count_vowels(const char *text)
{
  int count = 0;
  const char *vowels = "aeiouAEIOU";

  while (*text)
  {
    if (strchr(vowels, *text))
    {
      count++;
    }
    text++;
  }

  return count;
}

// Р¤СѓРЅРєС†РёСЏ РґР»СЏ СЃРѕР·РґР°РЅРёСЏ РјР°СЃСЃРёРІР° РїСЂРµРґР»РѕР¶РµРЅРёР№ СЃ Р±РѕР»РµРµ С‡РµРј M С‡РёСЃР»Р°РјРё
int is_number(const char *str)
{
  for (size_t i = 0; str[i] != '\0'; i++)
  {
    if (!isdigit(str[i]))
    {
      return 0; // Не число
    }
  }
  return 1; // Число
}

void create_sentences_array(const char *text, int M)
{
  char *text_copy = strdup(text);
  char *token;
  char **sentences = (char **)malloc(MAX_SENTENCES * sizeof(char *)); // Динамическое выделение памяти
  int sentence_count = 0;

  if (sentences == NULL)
  {
    fprintf(stderr, "Ошибка выделения памяти!\n");
    exit(1);
  }

  token = strtok(text_copy, ".!?\n"); // Добавлена обработка '\n'
  while (token != NULL && sentence_count < MAX_SENTENCES)
  {
    int number_count = 0;
    char *word;
    char *sentence_copy = strdup(token); // Копируем предложение для обработки

    if (sentence_copy == NULL)
    {
      fprintf(stderr, "Ошибка выделения памяти!\n");
      exit(1);
    }

    word = strtok(sentence_copy, " ");
    while (word != NULL)
    {
      if (is_number(word))
      {
        number_count++;
      }
      word = strtok(NULL, " ");
    }

    if (number_count > M)
    {
      sentences[sentence_count] = strdup(token); // Копируем предложение в массив

      if (sentences[sentence_count] == NULL)
      {
        fprintf(stderr, "Ошибка выделения памяти!\n");
        exit(1);
      }

      sentence_count++;
    }

    free(sentence_copy);           // Освобождаем память
    token = strtok(NULL, ".!?\n"); // Добавлена обработка '\n'
  }

  printf("Созданные предложения с более чем %d числами:\n", M);
  for (int i = 0; i < sentence_count; i++)
  {
    printf("%s.\n", sentences[i]);
    free(sentences[i]); // Освобождаем память
  }

  free(sentences); // Освобождаем память
  free(text_copy);
}

int main(int argc, char *argv[])
{
  SetConsoleOutputCP(CP_UTF8);
  if (argc < 3)
  {
    printf("РћС€РёР±РєР°: РЅРµРґРѕСЃС‚Р°С‚РѕС‡РЅРѕ Р°СЂРіСѓРјРµРЅС‚РѕРІ. РСЃРїРѕР»СЊР·СѓР№С‚Рµ:\n");
    printf("Lab6.exe \"РўРµРєСЃС‚ РґР»СЏ РѕР±СЂР°Р±РѕС‚РєРё\" -info 5\n");
    printf("РёР»Рё\n");
    printf("Lab6.exe \"РўРµРєСЃС‚ РґР»СЏ РѕР±СЂР°Р±РѕС‚РєРё\" -create 3\n");
    printf("РёР»Рё\n");
    printf("Lab6.exe \"РўРµРєСЃС‚ РґР»СЏ РѕР±СЂР°Р±РѕС‚РєРё\" -delete\n");
    return 1;
  }

  const char *text = argv[1];
  const char *command = argv[2];

  if (strcmp(command, "-info") == 0)
  {
    if (argc != 4)
    {
      printf("РћС€РёР±РєР°: РЅРµРІРµСЂРЅРѕРµ РєРѕР»РёС‡РµСЃС‚РІРѕ Р°СЂРіСѓРјРµРЅС‚РѕРІ РґР»СЏ РєРѕРјР°РЅРґС‹ '-info'.\n");
      return 1;
    }

    int vowel_count = count_vowels(text);
    printf("РљРѕР»РёС‡РµСЃС‚РІРѕ РіР»Р°СЃРЅС‹С… Р±СѓРєРІ: %d\n", vowel_count);
  }
  else if (strcmp(command, "-create") == 0)
  {
    if (argc != 4)
    {
      printf("РћС€РёР±РєР°: РЅРµРІРµСЂРЅРѕРµ РєРѕР»РёС‡РµСЃС‚РІРѕ Р°СЂРіСѓРјРµРЅС‚РѕРІ РґР»СЏ РєРѕРјР°РЅРґС‹ '-create'.\n");
      return 1;
    }

    int M = atoi(argv[3]);
    create_sentences_array(text, M);
  }
  else if (strcmp(command, "-delete") == 0)
  {
    if (argc != 3)
    {
      printf("РћС€РёР±РєР°: РЅРµРІРµСЂРЅРѕРµ РєРѕР»РёС‡РµСЃС‚РІРѕ Р°СЂРіСѓРјРµРЅС‚РѕРІ РґР»СЏ РєРѕРјР°РЅРґС‹ '-delete'.\n");
      return 1;
    }

    char text_copy[MAX_LENGTH * MAX_SENTENCES];
    strncpy(text_copy, text, sizeof(text_copy));
    text_copy[sizeof(text_copy) - 1] = '\0'; // РћР±РµСЃРїРµС‡РёС‚СЊ РЅСѓР»СЊ-С‚РµСЂРјРёРЅР°С†РёСЋ
    char *s = deleteSentencesWithNumbers(text_copy);
    printf("%s\n", s);
  }
  else
  {
    printf("РћС€РёР±РєР°: РЅРµРёР·РІРµСЃС‚РЅР°СЏ РєРѕРјР°РЅРґР° '%s'.\n", command);
    return 1;
  }

  return 0;
}