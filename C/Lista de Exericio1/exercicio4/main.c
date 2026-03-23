#include <stdio.h>

//Escreva um programa em C para ler 04 pares de valores inteiros e positivos, valide
//essa entrada. Para cada par lido deve ser impresso o valor do maior elemento do par
//ou a frase "Valores Iguais" quando o forem.


#include <stdio.h>

int main() {
    int a, b, i;

    for (i = 1; i <= 4; i++) {
        // Leitura e validação do primeiro valor
        do {
            printf("Par %d - Digite o primeiro valor (positivo): ", i);
            scanf("%d", &a);
        } while (a <= 0);

        // Leitura e validação do segundo valor
        do {
            printf("Par %d - Digite o segundo valor (positivo): ", i);
            scanf("%d", &b);
        } while (b <= 0);

        // Verificação
        if (a > b) {
            printf("Maior valor: %d\n\n", a);
        } else if (b > a) {
            printf("Maior valor: %d\n\n", b);
        } else {
            printf("Valores Iguais\n\n");
        }
    }

    return 0;
}