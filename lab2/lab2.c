
#include <stdio.h>

int main() {
    int A, B, C, Z, asm_Z, asm_result;

    printf("Input A, B, C values: \n");
    scanf("%d %d %d", &A, &B, &C);

    // ���������� Z = A - B + C
    asm("movl %1, %%eax;"
        "subl %2, %%eax;"
        "addl %3, %%eax;"
        "movl %%eax, %0;"
        : "=r" (asm_Z)
        : "g" (A), "g" (B), "g" (C)
        : "%eax");

    asm(
        "movl %4, %%eax;" // asm_Z -> EAX
        "cmp $0, %%eax;"  // ��������� EAX � 0
        "jle less_than;"   // �������, ���� EAX <= 0

        "movl $0, %%ebx;" // ������������� �������� ����� ������� 7
        "movl %1, %%ecx;" // ������������� �������� i
        "movl %%ebx, %%eax;" // EBX -> EAX

        "cmp %2, %%ecx;"  // ���������� ECX � B
        "jg exit;" // ���� > B, �� �� �������� ���� � result = 0

        "loop_start:"
        "movl %%ecx, %%eax;" // ECX -> EAX
        "cdq;"               // ���������
        "idivl %5;"          // EAX / 7 
        "cmp $0, %%edx;" // ���������� ������� �� ������� � 0
        "jne skip_add;"  // ���� ������� != 0, �� �� ���������

        "addl $1, %%ebx;" // ��������� 1 � �������� ������� 7

        "skip_add:"
        "addl $1, %%ecx;" // ����������� ECX �� 1
        "cmp %2, %%ecx;"  // ���������� ECX � B
        "jle loop_start;" // ���� <= B, �� ���������� ����

        "movl %%ebx, %%eax;" // EBX -> EAX
        "jmp exit;"          // ������� � ����� exit

        "less_than:"
        "movl %1, %%eax;"    // A -> EAX
        "addl %3, %%eax;"    // EAX += C //////
        "movl %%eax, %%ebx;" // A + C -> EBX
        "movl %2, %%eax;"    // B -> EAX
        "cdq;"               // ���������� EAX �� EDX:EAX ��� ����� ����� �����
        "idivl %3;"          // EAX / C
        "addl %%ebx, %%eax;" // EAX += EBX (A + C + B / C)

        "exit:"
        "movl %%eax, %0;" // EAX -> asm_result

        : "=r"(asm_result)
        : "r"(A), "r"(B), "r"(C), "r"(asm_Z), "r"(7)
        : "%eax", "%ebx", "%edx", "%ecx");

    Z = A - B + C;
    int result;
    if (Z <= 0)
    {
        result = A + C + B / C;
    }
    else
    {
        result = 0;
        int i;
        for (i = A; i <= B; ++i)
        {
            if (i % 7 == 0)
            {
                result++;
            }
        }
    }

    printf("C_Z: %d\n", Z);
    printf("ASM_Z: %d\n", asm_Z);
    printf("C_result: %d\n", result);
    printf("ASM_result: %d", asm_result);

    return 0;
}

