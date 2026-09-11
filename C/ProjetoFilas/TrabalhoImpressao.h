//
// Aula 03 - Projeto Filas
// Spooler de impressao com fila circular
//

#ifndef PROJETOFILAS_TRABALHOIMPRESSAO_H
#define PROJETOFILAS_TRABALHOIMPRESSAO_H

#include <stdbool.h>

// constantes
enum {
    TAMANHO = 5   // capacidade maxima da fila circular
};

// estrutura que representa um trabalho de impressao na fila
typedef struct {
    int id;                    // identificador unico do trabalho
    char nome_arquivo[100];    // nome do arquivo a ser impresso
    int num_paginas;           // total de paginas do arquivo
} TrabalhoImpressao;

// variaveis globais da fila (mesmo padrao usado em aula: array + inicio/fim + flag "vazia")
extern TrabalhoImpressao fila[TAMANHO];
extern int inicio;
extern int fim;
extern bool vazia;
extern int proximo_id;     // usado para gerar os ids sequencialmente

// protipos das funcoes da fila circular
void inicializa_fila();
bool esta_vazia();
bool esta_cheia();
bool adiciona_trabalho(TrabalhoImpressao trabalho);
bool processa_proximo_trabalho();
void visualiza_fila();

#endif //PROJETOFILAS_TRABALHOIMPRESSAO_H
