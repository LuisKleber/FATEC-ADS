#include <stdio.h>

//Sequência de Fibonacci Escreva um programa que leia um número inteiro positivo N e
//imprima os N primeiros termos da sequência de Fibonacci.
//Exemplo para N=5: 0 1 1 2 3

#include <stdio.h>

int main() {
    int N, i;
    int a = 0, b = 1, proximo;

    // Validação de N
    do {
        printf("Digite um numero inteiro positivo: ");
        scanf("%d", &N);
    } while (N <= 0);

    printf("Sequencia de Fibonacci:\n");

    for (i = 1; i <= N; i++) {
        printf("%d ", a);

        proximo = a + b;
        a = b;
        b = proximo;
    }

    return 0;
}
