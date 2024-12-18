﻿#include <stdio.h>
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
      return 0;
  }
  return 1;
}

void create_sentences_array(const char *text, int M)
{
  char *text_copy = strdup(text);
  char **sentences = (char **)malloc(MAX_SENTENCES * sizeof(char *));
  int sentence_count = 0;
  int start_index = 0;

  if (sentences == NULL)
  {
    fprintf(stderr, "Ошибка выделения памяти!\n");
    exit(1);
  }

  for (int i = 0; text_copy[i] != '\0'; ++i)
  {
    if (strchr(".!?\n", text_copy[i]) != NULL)
    {
      int len = i - start_index;
      char *sentence = (char *)malloc((len + 2) * sizeof(char)); // +1 for \0, +1 for potential trailing space

      if (sentence == NULL)
      {
        fprintf(stderr, "Ошибка выделения памяти!\n");
        exit(1);
      }
      strncpy(sentence, text_copy + start_index, len);
      sentence[len] = '\0';

      int number_count = 0;
      char *word_copy = strdup(sentence); // Создаем копию для strtok
      if (word_copy == NULL)
      {
        fprintf(stderr, "Ошибка выделения памяти!\n");
        exit(1);
      }
      char *word = strtok(word_copy, " ");
      while (word != NULL)
      {
        if (is_number(word))
        {
          number_count++;
        }
        word = strtok(NULL, " ");
      }
      free(word_copy); // Освобождаем память

      if (number_count > M)
      {
        sentences[sentence_count] = strdup(sentence);
        if (sentences[sentence_count] == NULL)
        {
          fprintf(stderr, "Ошибка выделения памяти!\n");
          exit(1);
        }
        sentence_count++;
      }
      free(sentence);
      start_index = i + 1;
    }
  }

  // Обработка последнего предложения
  int len = strlen(text_copy) - start_index;
  if (len > 0)
  {
    char *sentence = (char *)malloc((len + 1) * sizeof(char));
    if (sentence == NULL)
    {
      fprintf(stderr, "Ошибка выделения памяти!\n");
      exit(1);
    }
    strncpy(sentence, text_copy + start_index, len);
    sentence[len] = '\0';

    int number_count = 0;
    char *word_copy = strdup(sentence);
    if (word_copy == NULL)
    {
      fprintf(stderr, "Ошибка выделения памяти!\n");
      exit(1);
    }
    char *word = strtok(word_copy, " ");
    while (word != NULL)
    {
      if (is_number(word))
      {
        number_count++;
      }
      word = strtok(NULL, " ");
    }
    free(word_copy);

    if (number_count > M)
    {
      sentences[sentence_count] = strdup(sentence);
      if (sentences[sentence_count] == NULL)
      {
        fprintf(stderr, "Ошибка выделения памяти!\n");
        exit(1);
      }
      sentence_count++;
    }
    free(sentence);
  }

  printf("Созданные предложения с более чем %d числами:\n", M);
  for (int i = 0; i < sentence_count; i++)
  {
    printf("%s.\n", sentences[i]);
    free(sentences[i]);
  }

  free(sentences);
  free(text_copy);
}

void remove_all_numbers_in_sentences(char *text)
{
  int len = strlen(text);
  int write_index = 0;
  bool in_sentence = false;

  for (int i = 0; i < len; ++i)
  {
    if (text[i] == '!' || text[i] == '?' || text[i] == '.')
    {
      in_sentence = false; // Конец предложения
    }
    else if (text[i] != ' ')
    {
      in_sentence = true; // Начало предложения или слово внутри
    }

    if (in_sentence && isdigit(text[i]))
    {
      // Пропускаем все цифры в числе
      while (i < len && isdigit(text[i]))
      {
        i++;
      }
      i--; // Корректируем индекс
    }
    else
    {
      text[write_index++] = text[i];
    }
  }
  text[write_index] = '\0';
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
    remove_all_numbers_in_sentences(text);
    printf("Текст после удаления чисел: %s\n", text);
     // РћР±РµСЃРїРµС‡РёС‚СЊ РЅСѓР»СЊ-С‚РµСЂРјРёРЅР°С†РёСЋ
  }
  else
  {
    printf("РћС€РёР±РєР°: РЅРµРёР·РІРµСЃС‚РЅР°СЏ РєРѕРјР°РЅРґР° '%s'.\n", command);
    return 1;
  }

  return 0;
}