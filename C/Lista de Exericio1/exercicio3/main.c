#include <stdio.h>

//3) Faça o programa que apresenta a seguinte saída, perguntando ao usuário o número máximo (no exemplo, 9).
//Este número deve ser sempre ímpar.
//1 2 3 4 5 6 7 8 9
//2 3 4 5 6 7 8 9
//3 4 5 6 7 8 9
//4 5 6 7 8 9
//5 6 7 8 9
//6 7 8 9
//7 8 9
//8 9
//9

#include <stdio.h>

int main() {
    int n, i, j;

    // Validação: número ímpar
    do {
        printf("Digite um numero impar: ");
        scanf("%d", &n);
    } while (n % 2 == 0 || n <= 0);

    // Primeira parte (com espaços)
    for (i = 1; i <= n - 2; i++) {
        for (j = i; j <= n; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }

    // Parte final (sem espaços)
    for (i = n - 2; i <= n; i++) {
        for (j = i; j <= n; j++) {
            printf("%d", j);
        }
        printf("\n");
    }

    return 0;
}


