#include <stdio.h>

//Escreva um programa que leia 3 notas de 5 alunos e a média das notas dos exercícios
//realizados por eles. Calcular a média de aproveitamento, usando a fórmula: MA = (N1
//+ N2*2 + N3*3 + ME)/7.

#include <stdio.h>

int main() {
    float N1, N2, N3, ME, MA;
    int i;

    // Para 5 alunos
    for (i = 1; i <= 5; i++) {

        printf("\n=== Aluno %d ===\n", i);

        // Leitura das notas
        do {
            printf("Digite a nota N1: ");
            scanf("%f", &N1);
        } while (N1 < 0);

        do {
            printf("Digite a nota N2: ");
            scanf("%f", &N2);
        } while (N2 < 0);

        do {
            printf("Digite a nota N3: ");
            scanf("%f", &N3);
        } while (N3 < 0);

        do {
            printf("Digite a media dos exercicios (ME): ");
            scanf("%f", &ME);
        } while (ME < 0);

        // Cálculo da média de aproveitamento
        MA = (N1 + (N2 * 2) + (N3 * 3) + ME) / 7;

        // Resultado
        printf("Media de Aproveitamento (MA): %.2f\n", MA);
    }

    return 0;
}