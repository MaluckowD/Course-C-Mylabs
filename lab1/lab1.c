#include <stdio.h>

int main() {
    int A, B, C, D, E, F, res;

    printf("Input A, B, C, D, E, F values: \n");
    scanf("%d %d %d %d %d %d", &A, &B, &C, &D, &E, &F);


    // C * (A – D) - F / (B + E) + C / A
    asm(
        "movl %1, %%eax;"   // A -> EAX
        "subl %2, %%eax;"   // находим разность и записываем в EAX EAX - D -> EAX
        "movl %3, %%ebx;"   // C -> EBX
        "imull %%ebx, %%eax;" // EBX * EAX -> EAX
        "movl %%eax, %%ecx;" // EAX -> ECX (копируем значение выражения C * (A - D) из регистра EAX -> ECX)

        "movl %4, %%eax;"   // F -> EAX
        "movl %5, %%ebx;"   // B -> EBX
        "addl %6, %%ebx;"   // находим сумму EBX + E и записываем в -> EBX
        "movl $0, %%edx;"
		"cltd;"   // обнуление регистра EDX перед делением
        "idivl %%ebx;"       // EAX / EBX -> EAX ( F / (B + E))
        "subl %%eax, %%ecx;" // ECX - EAX -> ECX (находим разность двух выражений C * (A - D) - F / (B + E))

        "movl %3, %%eax;"   // C -> EAX
        "movl $0, %%edx;"
		"cltd;"   // обнуление регистра EDX перед делением
        "idivl %1;"          // EAX / A -> EAX (C / A)
        "addl %%eax, %%ecx;" // ECX + EAX -> ECX (находим финальную сумму с C / A)

        "movl %%ecx, %0;"   // ECX -> res
        : "=r" (res)
        : "r" (A), "r" (D), "r" (C), "r" (F), "r" (B), "r" (E)
        : "%eax", "%ebx", "%ecx", "%edx"
    );

    printf("Result: %d * (%d - %d) - %d / (%d + %d) + %d / %d = %d\n", C, A, D, F, B, E, C, A, res);
    res = C * (A - D) - F / (B + E) + C / A;
  	printf("%d", res);
    
    

    return 0;
}

