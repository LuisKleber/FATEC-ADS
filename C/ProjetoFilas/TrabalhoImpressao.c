#include <stdio.h>
#include "TrabalhoImpressao.h"

// variaveis da fila
TrabalhoImpressao fila[TAMANHO];
int inicio = 0;
int fim = 0;
bool vazia = true;
int proximo_id = 1;

// inicializa_fila: coloca a fila no estado inicial (vazia)
void inicializa_fila() {
    inicio = 0;
    fim = 0;
    vazia = true;
    proximo_id = 1;
}

// esta_vazia: verdadeiro quando nao ha nenhum trabalho na fila
bool esta_vazia() {
    return vazia;
}

// esta_cheia: verdadeiro quando inicio e fim se encontram e a fila NAO esta vazia
// (esse "encontro" so significa fila cheia se ja tiver algo dentro dela,
//  senao seria confundido com o estado inicial de fila vazia)
bool esta_cheia() {
    return (!vazia && inicio == fim);
}

// adiciona_trabalho: insere um novo trabalho no final da fila (posicao "fim")
bool adiciona_trabalho(TrabalhoImpressao trabalho) {
    if (esta_cheia()) {
        return false;
    }

    fila[fim] = trabalho;
    fim = (fim + 1) % TAMANHO;   // avanca "fim" de forma circular
    vazia = false;

    return true;
}

// processa_proximo_trabalho: remove e "processa" o trabalho que esta no inicio da fila
bool processa_proximo_trabalho() {
    if (esta_vazia()) {
        return false;
    }

    TrabalhoImpressao trabalho = fila[inicio];
    inicio = (inicio + 1) % TAMANHO;   // avanca "inicio" de forma circular

    if (inicio == fim) {
        vazia = true;   // consumiu o ultimo trabalho que havia na fila
    }

    printf("\nImprimindo trabalho #%d - \"%s\" (%d pagina(s))...\n",
           trabalho.id, trabalho.nome_arquivo, trabalho.num_paginas);
    printf("Trabalho #%d processado e removido da fila.\n", trabalho.id);

    return true;
}

// visualiza_fila: percorre a fila do inicio ate o fim e imprime cada trabalho
void visualiza_fila() {
    if (esta_vazia()) {
        printf("\nA fila de impressao esta vazia.\n");
        return;
    }

    printf("\n--- Fila de impressao ---\n");

    int i = inicio;
    do {
        printf("ID: %d | Arquivo: %-20s | Paginas: %d\n",
               fila[i].id, fila[i].nome_arquivo, fila[i].num_paginas);
        i = (i + 1) % TAMANHO;
    } while (i != fim);

    printf("--------------------------\n");
}
