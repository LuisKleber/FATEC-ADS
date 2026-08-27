//
// Implementação da pilha de caracteres
//
#include "Pilha.h"

// variáveis
char pilha[TAMANHO];
int posicao = 0;

// funções

// coloca um caractere no topo da pilha
bool push(char dado) {
    if (posicao == TAMANHO) {
        // pilha cheia, não dá pra colocar mais nada
        return false;
    } else {
        pilha[posicao] = dado;
        posicao++;
        return true;
    }
}

// retira o caractere do topo da pilha e devolve em *dado
bool pop(char *dado) {
    if (posicao == 0) {
        // pilha vazia, não tem o que tirar
        return false;
    } else {
        posicao--;
        *dado = pilha[posicao];
        return true;
    }
}

// verifica se a pilha está vazia (usada no final do algoritmo)
bool pilhaVazia() {
    return posicao == 0;
}
