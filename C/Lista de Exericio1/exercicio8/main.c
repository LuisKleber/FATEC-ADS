#include <stdio.h>

//Faça um programa que receba 10 dados do usuário e mostre a média dos valores
//entrados pelo usuário, use a estrutura while, para receber dez valores ou sair quando o
//usuário entrar com o valor 0.

#include <stdio.h>

int main() {
    int count = 0;
    float num, soma = 0, media;

    printf("Digite ate 10 valores (0 para sair):\n");

    while (count < 10) {
        printf("Valor %d: ", count + 1);
        scanf("%f", &num);

        if (num == 0) {
            break; // encerra antes dos 10 valores
        }

        soma += num;
        count++;
    }

    // Verifica se houve entrada válida
    if (count > 0) {
        media = soma / count;
        printf("\nMedia dos valores: %.2f\n", media);
    } else {
        printf("\nNenhum valor valido foi informado.\n");
    }

    return 0;
}