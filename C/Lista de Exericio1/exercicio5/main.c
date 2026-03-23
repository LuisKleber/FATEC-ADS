#include <stdio.h>

//Escreva um programa que leia 05 números inteiros positivos. Para cada número
//informado escrever a soma de seus divisores (exceto ele mesmo).

#include <stdio.h>

int main() {
    int num, i, j, soma;

    // Ler 5 números
    for (i = 1; i <= 5; i++) {

        // Validação (número positivo)
        do {
            printf("Digite o %dº numero (positivo): ", i);
            scanf("%d", &num);
        } while (num <= 0);

        soma = 0;

        // Calcular soma dos divisores (exceto ele mesmo)
        for (j = 1; j < num; j++) {
            if (num % j == 0) {
                soma += j;
            }
        }

        // Resultado
        printf("Soma dos divisores de %d (exceto ele): %d\n\n", num, soma);
    }

    return 0;
}