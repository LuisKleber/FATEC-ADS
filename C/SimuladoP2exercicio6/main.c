/*
 * EXERCÍCIO 6: Aritmética de Ponteiros e Navegação de Vetores
 * ============================================================
 * Objetivo:
 *   Percorrer e imprimir um vetor de 10 floats usando APENAS aritmética
 *   de ponteiros. Proibido usar colchetes [ ] ou índices numéricos.
 *
 * CONCEITOS-CHAVE:
 *   - Um vetor em C é, na essência, um PONTEIRO para seu primeiro elemento.
 *   - float *p = vet;  → p aponta para vet[0]
 *   - p++              → avança o ponteiro em sizeof(float) bytes (geralmente 4)
 *   - *p               → acessa o valor no endereço atual apontado por p
 *   - p++  ≠  (*p)++   → p++ muda o ENDEREÇO; (*p)++ muda o VALOR no endereço
 *
 * ARITMÉTICA DE PONTEIROS:
 *   Se float ocupa 4 bytes e p aponta para o endereço 0x1000:
 *     p+0 → 0x1000 (vet[0])
 *     p+1 → 0x1004 (vet[1])  ← C calcula automaticamente: endereço + n*sizeof(tipo)
 *     p+2 → 0x1008 (vet[2])
 *     ...
 */

#include <stdio.h>

int main() {
    /* Vetor de 10 floats já inicializado */
    float vet[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

    /* -------------------------------------------------------
     * p recebe o ENDEREÇO do primeiro elemento do vetor.
     * Equivalente a: float *p = &vet[0];
     * O nome do vetor já é o endereço do 1º elemento em C.
     * ------------------------------------------------------- */
    float *p = vet;

    printf("=== Navegacao por Aritmetica de Ponteiros ===\n");
    printf("Endereço inicial de p: %p\n\n", (void*)p);

    /* -------------------------------------------------------
     * Loop usando PONTEIRO:
     *   - p começa em vet[0]
     *   - Condição: p < vet + 10  → enquanto não ultrapassar o último
     *     (vet + 10 é o endereço UMA POSIÇÃO após o último elemento)
     *   - p++ avança para o próximo float a cada iteração
     * ------------------------------------------------------- */
    int posicao = 0;
    while (p < vet + 10) {
        printf("  Posicao %2d | Endereco: %p | Valor: %.1f\n",
               posicao,
               (void*)p,   /* Endereço atual do ponteiro */
               *p);         /* Valor no endereço atual — operador de conteúdo */
        p++;                /* Avança o ponteiro para o próximo float */
        posicao++;
    }

    /* -------------------------------------------------------
     * VERSÃO ALTERNATIVA: loop for (igualmente sem colchetes)
     * ------------------------------------------------------- */
    printf("\n=== Versao com for ===\n");
    for (p = vet; p < vet + 10; p++) {
        printf("%.1f ", *p);
    }
    printf("\n");

    /* -------------------------------------------------------
     * DEMONSTRAÇÃO: diferença entre p++ e (*p)++
     * ------------------------------------------------------- */
    printf("\n=== Demonstracao: p++ vs (*p)++ ===\n");
    p = vet;                      /* Volta p para o início */
    printf("Valor em *p antes       : %.1f\n", *p);
    printf("Endereco de p antes     : %p\n", (void*)p);

    p++;                          /* Avança o PONTEIRO — p agora aponta para vet[1] */
    printf("\nApos p++:\n");
    printf("  Endereco de p agora   : %p  (avancou %lu bytes)\n",
           (void*)p, sizeof(float));
    printf("  Valor em *p agora     : %.1f  (eh vet[1])\n", *p);

    return 0;
}

/*
 * POR QUE p < vet + 10 E NÃO p <= vet + 9?
 *   Ambos são equivalentes numericamente, mas  p < vet + 10  é o
 *   idioma padrão em C para loops de ponteiro — mais legível e seguro.
 *   vet + 10 aponta para o endereço logo após o vetor (não acessamos
 *   este endereço, apenas usamos como sentinela de parada).
 */
