#include <stdio.h>
//Fazer um programa em C para calcular a somatória dos N primeiros divisores de um
//inteiro X, onde N e X são lidos e são números inteiros e positivos. [Validar entradas].


int main(void) {

    int n, x, s;
    int soma = 0;
    int cont = 0;

    printf("Digite o valor de x (inteiro positivo): ");
    scanf("%d", &x);
    printf("Digite o valor de n (inteiro positivo): ");
    scanf("%d", &n);
    if (x <= 0 || n <= 0) {
        printf("Valores invalidos ! \n:");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (x % 1 == 0) {
            soma += i;
            cont += 1;
            if (cont == n) {
                break;
            }
        }
    }
    printf("Somatoria dos %d primeiros divisores de %d=%d\n: ", n,x, soma);
    return 0;
}