#include <stdio.h>

//Fatorial de um Número: Faça um programa que leia um número inteiro positivo e
//calcule o seu fatorial N!. O programa deve validar se o número digitado é negativo e
//pedir uma nova entrada caso seja.

#include <stdio.h>

int main() {
    int n, i;
    unsigned long long fatorial = 1;

    // Validação: não aceitar número negativo
    do {
        printf("Digite um numero inteiro nao negativo: ");
        scanf("%d", &n);
    } while (n < 0);

    // Cálculo do fatorial
    for (i = 1; i <= n; i++) {
        fatorial *= i;
    }

    // Resultado
    printf("Fatorial de %d = %llu\n", n, fatorial);

    return 0;
}