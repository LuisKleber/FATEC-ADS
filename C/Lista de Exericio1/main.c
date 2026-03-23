#include <stdio.h>

int main(void) {
    int n;
    int melhorVolta;
    int t;
    float tempo, melhorTempo, soma = 0, media;

    do {
        printf("Digite o numero de voltas: (1...15):  ");
        scanf("%d", &n);
    } while ( n < 0 || n > 15 );
    for (int i = 0; i < n; i++) {
    printf("Digite o tempo de voltas : ", t);
        scanf("%f", &tempo);
        soma += tempo;

        if (tempo == 1 || tempo < melhorVolta) {
            melhorTempo = tempo;
            melhorVolta = t;
        }
    }
    media = soma / n;
    printf("Media: %.2f\n: ", melhorTempo);
    printf("Volta com melhor Tempo: %d\n", melhorVolta);
    printf("Tempo medio das voltas: %f\n", media);

    return 0;
}