/*
 * EXERCÍCIO 1: Matrizes e Pré-processador
 * =========================================
 * Objetivo:
 *   1. Calcular a SOMA dos elementos ESTRITAMENTE ACIMA da diagonal principal.
 *   2. Multiplicar os elementos da DIAGONAL SECUNDÁRIA pelo maior valor da 1ª linha.
 *
 * CONCEITOS-CHAVE:
 *   - #define DIM 5  → constante de pré-processador (substituição textual em tempo de compilação).
 *   - Diagonal principal: elementos onde coluna == linha (i == j).
 *   - "Estritamente acima": coluna > linha (j > i).
 *   - Diagonal secundária: elementos onde i + j == DIM - 1.
 */

#include <stdio.h>


#define DIM 5   /* Constante de pré-processador: altere aqui para mudar toda a lógica */

int main() {
    int matriz[DIM][DIM];
    int soma_acima = 0;
    int maior_primeira_linha;

    /* -------------------------------------------------------
     * PASSO 1: Preenchimento da matriz
     * Percorremos linha por linha (i) e coluna por coluna (j).
     * ------------------------------------------------------- */
    printf("=== Preenchimento da Matriz %dx%d ===\n", DIM, DIM);
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            printf("matriz[%d][%d] = ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    /* -------------------------------------------------------
     * PASSO 2: Exibir a matriz para conferência visual
     * ------------------------------------------------------- */
    printf("\n=== Matriz Lida ===\n");
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            printf("%4d", matriz[i][j]);
        }
        printf("\n");
    }

    /* -------------------------------------------------------
     * PASSO 3: Encontrar o MAIOR valor da PRIMEIRA LINHA (i=0)
     * Inicializamos com o primeiro elemento e comparamos os demais.
     * ------------------------------------------------------- */
    maior_primeira_linha = matriz[0][0];
    for (int j = 1; j < DIM; j++) {
        if (matriz[0][j] > maior_primeira_linha) {
            maior_primeira_linha = matriz[0][j];
        }
    }
    printf("\nMaior valor da 1 linha: %d\n", maior_primeira_linha);

    /* -------------------------------------------------------
     * PASSO 4: Calcular a SOMA dos elementos ACIMA da diagonal
     * Condição: j > i  (a coluna é maior que a linha)
     *
     * Exemplo para DIM=3:
     *   [0][1], [0][2], [1][2]  → triângulo superior sem a diagonal
     * ------------------------------------------------------- */
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (j > i) {               /* Estritamente acima da diagonal */
                soma_acima += matriz[i][j];
            }
        }
    }
    printf("Soma dos elementos acima da diagonal principal: %d\n", soma_acima);

    /* -------------------------------------------------------
     * PASSO 5: Multiplicar a DIAGONAL SECUNDÁRIA pelo maior da 1ª linha
     * Diagonal secundária: i + j == DIM - 1
     *
     * Exemplo para DIM=5:
     *   [0][4], [1][3], [2][2], [3][1], [4][0]
     * ------------------------------------------------------- */
    printf("\n=== Diagonal Secundaria (apos multiplicacao) ===\n");
    for (int i = 0; i < DIM; i++) {
        int j = (DIM - 1) - i;          /* j calculado diretamente, sem varrer a matriz toda */
        matriz[i][j] *= maior_primeira_linha;
        printf("  matriz[%d][%d] = %d\n", i, j, matriz[i][j]);
    }

    /* -------------------------------------------------------
     * PASSO 6: Exibir a matriz modificada
     * ------------------------------------------------------- */
    printf("\n=== Matriz Final (diagonal secundaria modificada) ===\n");
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            printf("%6d", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}
