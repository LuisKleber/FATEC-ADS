#include <stdio.h>
/*
 * EXERCÍCIO 2: Processamento de Strings e Validação de Delimitadores
 * ====================================================================
 * Objetivo:
 *   - Receber uma frase.
 *   - Inverter cada PALAVRA individualmente (não a frase toda).
 *   - Substituir os ESPAÇOS por sublinhado (_).
 *
 * CONCEITOS-CHAVE:
 *   - fgets(): lê a linha inteira com proteção de buffer (seguro, diferente de gets).
 *   - '\0' (nulo): sentinela que marca o fim de qualquer string em C.
 *   - '\n': fgets inclui o newline; precisamos tratar isso.
 *   - Inversão in-place: usamos dois índices (início e fim) caminhando um ao outro.
 */

#include <string.h>

/*
 * inverter_palavra()
 * ------------------
 * Recebe um ponteiro para o início de uma palavra e seu comprimento.
 * Troca os caracteres das extremidades até o meio (algoritmo two-pointer).
 *
 * Exemplo: "casa" → início=0, fim=3
 *   Troca [0]'c' com [3]'a' → "asac" → não, relendo:
 *   Troca s[0]↔s[3]: 'c'↔'a' → "asac" → aguarda: "asa" depois "asa"
 *   Troca s[1]↔s[2]: 'a'↔'s' → "acsa" → resultado: "asac"
 *   Correto: c-a-s-a → a-s-a-c ✓
 */
void inverter_palavra(char *inicio, int tamanho) {
    int esq = 0;
    int dir = tamanho - 1;

    while (esq < dir) {
        /* Troca clássica com variável temporária */
        char temp  = inicio[esq];
        inicio[esq] = inicio[dir];
        inicio[dir] = temp;
        esq++;
        dir--;
    }
}

/*
 * gerar_versao_seguranca()
 * -------------------------
 * Percorre a string caractere a caractere.
 * Quando encontra o fim de uma palavra (espaço, '_' ou '\0'), inverte o trecho.
 * Depois substitui espaços por '_'.
 */
void gerar_versao_seguranca(char *frase) {
    int i = 0;
    int inicio_palavra = 0;   /* Marca onde a palavra atual começou */

    /* Percorremos até o '\0' (fim de string), incluindo-o como "separador" final */
    while (frase[i] != '\0') {

        /* Chegou em um delimitador (espaço ou newline deixado pelo fgets) */
        if (frase[i] == ' ' || frase[i] == '\n') {

            /* Inverte a palavra que terminou antes deste caractere */
            int tamanho_palavra = i - inicio_palavra;
            if (tamanho_palavra > 0) {
                inverter_palavra(&frase[inicio_palavra], tamanho_palavra);
            }

            /* Substitui espaço por sublinhado. '\n' vira '_' também — limpamos abaixo. */
            if (frase[i] == ' ') {
                frase[i] = '_';
            } else {
                /* Remove o '\n' deixado pelo fgets, colocando terminador */
                frase[i] = '\0';
                break;   /* Fim da frase útil */
            }

            inicio_palavra = i + 1;  /* Próxima palavra começa após o separador */
        }

        i++;
    }

    /* Caso a frase não termine com '\n' (última palavra sem separador após ela) */
    int tamanho_final = i - inicio_palavra;
    if (tamanho_final > 0) {
        inverter_palavra(&frase[inicio_palavra], tamanho_final);
    }
}

int main() {
    char buffer[100];

    printf("Digite a frase: ");

    /*
     * fgets(buffer, sizeof(buffer), stdin):
     *   - Lê até 99 caracteres + '\0'
     *   - Inclui o '\n' do Enter na string
     *   - NUNCA estoura o buffer (diferente do gets obsoleto)
     */
    fgets(buffer, sizeof(buffer), stdin);

    gerar_versao_seguranca(buffer);

    printf("Versao de seguranca: %s\n", buffer);

    return 0;
}

/*
 * EXEMPLO DE EXECUÇÃO:
 *   Entrada : "ola mundo cruel"
 *   Saída   : "alo_odnum_leurc"
 *
 *   Cada palavra foi invertida individualmente e os espaços viraram '_'.
 */
