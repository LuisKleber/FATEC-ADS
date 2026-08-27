//
// Pilha de caracteres - usada no algoritmo de balanceamento
//

#ifndef PILHA_PILHA_H
#define PILHA_PILHA_H
#include <stdbool.h>

// constantes
enum {
    TAMANHO = 100
};

// variáveis
extern char pilha[];
extern int posicao;

// protótipos
bool push(char dado);
bool pop(char *dado);
bool pilhaVazia();

#endif //PILHA_PILHA_H
