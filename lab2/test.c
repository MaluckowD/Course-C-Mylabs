#include <stdio.h>

int main(void)
{
    int A, B, C, asm_Z, asm_result;
    printf("Input A, B, C values: \n");
    scanf("%d %d %d", &A, &B, &C);

    asm("movl %1, %%eax;"
        "subl %2, %%eax;"
        "addl %3, %%eax;"
        "movl %%eax, %0;"
        : "=r" (asm_Z)
        : "g" (A), "g" (B), "g" (C)
        : "%eax");

    asm(
        "movl %4, %%eax;" // asm_Z -> EAX
        "cmp $0, %%eax;"  // Сравнение EAX с 0
        "jg less_than;"   // Переход, если EAX > 0

        "movl $0, %%ebx;" // Инициализация суммы
        "movl %1, %%ecx;" // Инициализация счётчика
        "movl %%ebx, %%eax;" // EBX -> EAX

        "cmp %2, %%ecx;"  // Сравниваем ECX с B
        "jg exit;" // Если > B, то не начинаем цикл и result = 0

        "loop_start:"
        "movl %%ecx, %%eax;" // ECX -> EAX
        "cdq;"               // Расширяем
        "idivl %5;"          // EAX / 2   ERROR

        "cmp $1, %%edx;" // Сравниваем в EDX
        "jne skip_add;"  // Если != 1, то не добавляем

        "addl %%ecx, %%ebx;" // Добавляем к ebx новое число

        "skip_add:"
        "addl $1, %%ecx;" // Увеличиваем ECX на 1
        "cmp %2, %%ecx;"  // Сравниваем ECX с B
        "jle loop_start;" // Если <= B, то продолжаем цикл

        "movl %%ebx, %%eax;" // EBX -> EAX
        "jmp exit;"          // Переход к метке exit

        "less_than:"
        "movl %1, %%eax;"    // A -> EAX
        "addl %2, %%eax;"    // EAX += B
        "movl %%eax, %%ebx;" // A + B -> EBX
        "movl %2, %%eax;"    // B -> EAX
        "cdq;"               // расширение EAX до EDX:EAX для учета знака числа
        "idivl %3;"          // EAX / C
        "addl %%ebx, %%eax;" // EAX += EBX (A + B + B / C)

        "exit:"
        "movl %%eax, %0;" // EAX -> asm_result

        : "=r"(asm_result)
        : "r"(A), "r"(B), "r"(C), "r"(asm_Z), "r"(2)
        : "%eax", "%ebx", "%edx", "%ecx");

    int Z = A * B * C;
    int result;
    if (Z > 0)
    {
        result = A + B + B / C;
    }
    else
    {
        result = 0;
        int i;
        for (i = A; i <= B; ++i)
        {
            if (i % 2 == 1)
            {
                result += i;
            }
        }
    }

    printf("C_Z: %d\n", Z);
    printf("ASM_Z: %d\n", asm_Z);
    printf("C_result: %d\n", result);
    printf("ASM_result: %d", asm_result);

    return 0;
}
