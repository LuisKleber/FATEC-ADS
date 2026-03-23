#include <stdio.h>
//Durante uma corrida de automóveis com N voltas (onde 0 < N < 15) de duração foram
//anotados, para um piloto, na ordem, os tempos registrados em cada volta. Fazer um
// em C para ler os tempos das N voltas. Calcular e imprimir: a) melhor tempo;
//b) a volta em que o melhor tempo ocorreu; c) tempo médio das N voltas.


#include <stdio.h>

int main() {
    int N, i, voltaMelhor;
    float tempos[15], melhorTempo, soma = 0, media;

    // Validação de N
    do {
        printf("Digite o numero de voltas (1 a 14): ");
        scanf("%d", &N);
    } while (N <= 0 || N >= 15);

    // Leitura dos tempos
    for (i = 0; i < N; i++) {
        do {
            printf("Digite o tempo da volta %d: ", i + 1);
            scanf("%f", &tempos[i]);
        } while (tempos[i] <= 0); // valida tempo positivo

        soma += tempos[i];
    }

    // Inicializa com a primeira volta
    melhorTempo = tempos[0];
    voltaMelhor = 1;

    // Encontrar melhor tempo
    for (i = 1; i < N; i++) {
        if (tempos[i] < melhorTempo) {
            melhorTempo = tempos[i];
            voltaMelhor = i + 1;
        }
    }

    // Calcular média
    media = soma / N;

    // Resultados
    printf("\n===== RESULTADOS =====\n");
    printf("Melhor tempo: %.2f\n", melhorTempo);
    printf("Volta do melhor tempo: %d\n", voltaMelhor);
    printf("Tempo medio: %.2f\n", media);

    return 0;
}