#include <stdio.h>

//Faça um programa que com uso da estrutura for. Determine se um número dado pelo
//usuário é primo, ou não.

#include <stdio.h>

int main() {
    int num, i, primo = 1;

    // Leitura e validação (número positivo maior que 1)
    do {
        printf("Digite um numero inteiro positivo maior que 1: ");
        scanf("%d", &num);
    } while (num <= 1);

    // Verificação se é primo
    for (i = 2; i < num; i++) {
        if (num % i == 0) {
            primo = 0;
            break;
        }
    }

    // Resultado
    if (primo == 1) {
        printf("O numero %d eh PRIMO.\n", num);
    } else {
        printf("O numero %d NAO eh primo.\n", num);
    }

    return 0;
}