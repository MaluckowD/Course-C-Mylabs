#include <stdio.h>

int main()
{
  int A, B, C, D, E, F, res;                     // объявляем переменные
  printf("Input A, B, C, D, E, F values: \n");   // выводим на экран подсказку для ввода
  scanf("%d%d%d%d%d%d", &A, &B, &C, &D, &E, &F); // запрашиваем значения переменных

  // расчитываем результат операции
  asm("movl %1, %%eax;"
      "movl %2, %%ebx;"
      "subl %3, %%eax;"

      // "movl %5, %%ebx;"
      // "addl %%ebx, %%eax;"
      // "idivl %%ecx;"
      // "movl %%ecx, %%eax;"
      // "movl %6, %%ebx;"
      // "idivl %%ebx;"
      // "subl %%ebx, %%eax;"
       "movl %%eax, %0;"
      : "=r"(res)
      /*A -> EAX*/
      /*B -> EBX*/
      /*D -> ECX*/
      /*E -> EBX*/
      /*C * (A - D) -> EAX*/
      /*F -> EBX*/
      /*F / (B + E) -> EBX*/
      /*C / A -> EAX*/
      /*(C * (A - D)) - (F / (B + E)) + (C / A) -> res*/
      : "r"(A), "r"(B)
      : "%eax", "%ebx", "%ecx");

  printf("Result: %d * (%d - %d) - %d / (%d + %d) + %d / %d = %d", C, A, D, F, B, E, C, A, res); // выводим на экран полученный результат выражения

  return 0;
}