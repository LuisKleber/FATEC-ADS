#include <stdio.h>
#include <string.h>
#include "TrabalhoImpressao.h"

// constantes do menu
enum {
    OP_NAO_SELECIONADA = 0,
    OP_ADICIONAR,
    OP_PROCESSAR,
    OP_VISUALIZAR,
    OP_SAIR
};

// protótipos
int menu();
void limpa_buffer_entrada();

int main(void) {
    int opcao = OP_NAO_SELECIONADA;

    inicializa_fila();

    while (opcao != OP_SAIR) {
        opcao = menu();

        switch (opcao) {
            case OP_ADICIONAR: {
                if (esta_cheia()) {
                    printf("\nFila cheia! Nao e possivel adicionar novo trabalho.\n");
                    break;
                }

                TrabalhoImpressao novo;
                novo.id = proximo_id;

                printf("Nome do arquivo: ");
                fgets(novo.nome_arquivo, sizeof(novo.nome_arquivo), stdin);
                novo.nome_arquivo[strcspn(novo.nome_arquivo, "\n")] = '\0'; // remove o \n do fgets

                printf("Numero de paginas: ");
                scanf("%d", &novo.num_paginas);
                limpa_buffer_entrada();

                if (adiciona_trabalho(novo)) {
                    printf("Trabalho #%d adicionado a fila.\n", novo.id);
                    proximo_id++;
                } else {
                    printf("Nao foi possivel adicionar o trabalho.\n");
                }
                break;
            }

            case OP_PROCESSAR:
                if (!processa_proximo_trabalho()) {
                    printf("\nFila vazia! Nao ha trabalhos para processar.\n");
                }
                break;

            case OP_VISUALIZAR:
                visualiza_fila();
                break;

            case OP_SAIR:
                printf("\nEncerrando o spooler de impressao...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    }

    return 0;
}

// exibe o menu e le a opcao escolhida pelo usuario
int menu() {
    int op = OP_NAO_SELECIONADA;

    printf("\n===== Spooler de Impressao =====\n");
    printf("%d - Adicionar trabalho\n", OP_ADICIONAR);
    printf("%d - Processar proximo trabalho\n", OP_PROCESSAR);
    printf("%d - Visualizar fila\n", OP_VISUALIZAR);
    printf("%d - Sair\n", OP_SAIR);
    printf("Digite sua opcao: ");

    scanf("%d", &op);
    limpa_buffer_entrada();

    return op;
}

// descarta o restante da linha no buffer de entrada (inclusive o \n deixado pelo scanf)
void limpa_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
