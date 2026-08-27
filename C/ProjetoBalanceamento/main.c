#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Pilha.h"

// Protótipos
bool balanceado(char *expressao);

int main(void) {
    char expressao[200];

    printf("Digite uma expressao numerica (ex: (2*{25+(55/2)})/3): ");
    fgets(expressao, sizeof(expressao), stdin);

    // fgets pega o \n do final, entao tiramos ele da string
    expressao[strcspn(expressao, "\n")] = '\0';

    if (balanceado(expressao)) {
        printf("A expressao esta BALANCEADA\n");
    } else {
        printf("A expressao esta DESBALANCEADA\n");
    }

    return EXIT_SUCCESS;
}

// Percorre a expressao caractere por caractere usando uma pilha
// para conferir se os parenteses e chaves estao balanceados
bool balanceado(char *expressao) {
    char caractereAberto;
    int i;

    // zera a pilha antes de comecar, caso a funcao seja chamada mais de uma vez
    posicao = 0;

    for (i = 0; expressao[i] != '\0'; i++) {

        // se for uma abertura, guarda na pilha
        if (expressao[i] == '(' || expressao[i] == '{') {
            push(expressao[i]);
        }

        // se for um fechamento, precisa tirar da pilha e conferir se combina
        else if (expressao[i] == ')' || expressao[i] == '}') {

            // tentou fechar algo mas a pilha ja estava vazia -> desbalanceado
            if (!pop(&caractereAberto)) {
                return false;
            }

            // fechou parenteses mas o que estava guardado era uma chave (ou vice versa)
            if (expressao[i] == ')' && caractereAberto != '(') {
                return false;
            }
            if (expressao[i] == '}' && caractereAberto != '{') {
                return false;
            }
        }

        // qualquer outro caractere (numero, +, -, *, / etc) e ignorado
    }

    // no final, se sobrou algo na pilha e porque ficou parenteses/chave sem fechar
    return pilhaVazia();
}
