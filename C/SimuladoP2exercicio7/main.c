/*
 * EXERCÍCIO 7: Estruturas de Dados Heterogêneas (Structs)
 * =========================================================
 * Objetivo:
 *   - Definir a struct Livro (título, autor, ano, preço).
 *   - Implementar função que receba por REFERÊNCIA e aplique 10% de desconto.
 *   - Usar OBRIGATORIAMENTE o operador seta (->) dentro da função.
 *
 * CONCEITOS-CHAVE:
 *   - struct: agrupa campos de tipos diferentes em uma única entidade.
 *   - Operador ponto (.)  : acessa campo de uma struct diretamente.
 *       ex: livro.preco = 50.0;
 *   - Operador seta (->) : acessa campo de uma struct através de PONTEIRO.
 *       ex: ptr->preco = 50.0;   equivale a  (*ptr).preco = 50.0;
 *   - Passagem por referência: evita copiar toda a struct na pilha,
 *     e permite modificar os dados originais.
 *
 * REGRA: se temos instância direta → usa ponto (.)
 *        se temos ponteiro para struct → usa seta (->)
 */

#include <stdio.h>
#include <string.h>

/* -------------------------------------------------------
 * Definição da struct Livro
 * Agrupa todos os atributos de um livro em um único tipo.
 * ------------------------------------------------------- */
struct Livro {
    char  titulo[50];   /* Título do livro */
    char  autor[50];    /* Nome do autor */
    int   ano;          /* Ano de publicação */
    float preco;        /* Preço em reais */
};

/* -------------------------------------------------------
 * Protótipos das funções
 * ------------------------------------------------------- */
void aplicar_desconto(struct Livro *l);
void imprimir_livro(struct Livro *l);
void preencher_livro(struct Livro *l);

/* -------------------------------------------------------
 * aplicar_desconto()
 * ------------------
 * Recebe um PONTEIRO para Livro (passagem por referência).
 * Usa o operador -> para acessar e modificar o campo preco.
 *
 * l->preco  é equivalente a  (*l).preco
 * O operador -> é um atalho que:
 *   1. Desreferencia o ponteiro (*)
 *   2. Acessa o campo (.preco)
 * ------------------------------------------------------- */
void aplicar_desconto(struct Livro *l) {
    /* Desconto de 10%: novo_preco = preco_original * 0.90 */
    l->preco = l->preco * 0.90f;

    /* Alternativa equivalente (menos elegante):
     * (*l).preco = (*l).preco * 0.90f;
     */
}

/* -------------------------------------------------------
 * imprimir_livro()
 * ----------------
 * Recebe o livro por referência para não copiar a struct.
 * Usa -> para leitura dos campos (mesma sintaxe para leitura
 * e escrita via ponteiro).
 * ------------------------------------------------------- */
void imprimir_livro(struct Livro *l) {
    printf("  Titulo : %s\n", l->titulo);
    printf("  Autor  : %s\n", l->autor);
    printf("  Ano    : %d\n", l->ano);
    printf("  Preco  : R$ %.2f\n", l->preco);
}

/* -------------------------------------------------------
 * preencher_livro()
 * -----------------
 * Preenche os campos da struct via ponteiro.
 * Usa scanf + fgets para strings e scanf para números.
 * ------------------------------------------------------- */
void preencher_livro(struct Livro *l) {
    /* Limpa o buffer antes do fgets */
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("  Titulo : ");
    fgets(l->titulo, sizeof(l->titulo), stdin);
    /* Remove o '\n' que o fgets inclui */
    l->titulo[strcspn(l->titulo, "\n")] = '\0';

    printf("  Autor  : ");
    fgets(l->autor, sizeof(l->autor), stdin);
    l->autor[strcspn(l->autor, "\n")] = '\0';

    printf("  Ano    : ");
    scanf("%d", &l->ano);

    printf("  Preco  : R$ ");
    scanf("%f", &l->preco);
}

/* Precisamos de string.h para strcspn usado acima */


int main() {
    /* -------------------------------------------------------
     * FORMA 1: struct preenchida estaticamente (para demonstração)
     * Acesso direto → usa ponto (.)
     * ------------------------------------------------------- */
    struct Livro livro1;

    /* Preenchimento com ponto — instância direta, não ponteiro */
    livro1.ano   = 2019;
    livro1.preco = 89.90f;

    /* Para strings usamos funções da <string.h> */
    strcpy(livro1.titulo, "O Programador Pragmatico");
    strcpy(livro1.autor,  "Andrew Hunt e David Thomas");

    printf("=== Livro 1 (antes do desconto) ===\n");
    imprimir_livro(&livro1);     /* Passamos o ENDEREÇO para a função */

    aplicar_desconto(&livro1);   /* A função modifica o original via ponteiro */

    printf("\n=== Livro 1 (apos 10%% de desconto) ===\n");
    imprimir_livro(&livro1);

    /* -------------------------------------------------------
     * FORMA 2: struct preenchida interativamente pelo usuário
     * ------------------------------------------------------- */
    printf("\n=== Cadastro de Novo Livro ===\n");
    struct Livro livro2;

    preencher_livro(&livro2);

    printf("\n=== Livro 2 (antes do desconto) ===\n");
    imprimir_livro(&livro2);

    aplicar_desconto(&livro2);

    printf("\n=== Livro 2 (apos 10%% de desconto) ===\n");
    imprimir_livro(&livro2);

    /* -------------------------------------------------------
     * DEMONSTRAÇÃO VISUAL: ponto vs seta
     * ------------------------------------------------------- */
    printf("\n=== Demonstracao: ponto (.) vs seta (->) ===\n");

    struct Livro exemplo;
    exemplo.preco = 100.0f;   /* Acesso direto com ponto */

    struct Livro *ptr = &exemplo;
    ptr->preco = 200.0f;      /* Acesso via ponteiro com seta */

    printf("  Apos ptr->preco = 200: exemplo.preco = %.2f\n", exemplo.preco);
    printf("  ptr->preco e exemplo.preco apontam para o MESMO dado!\n");

    return 0;
}

/*
 * RESUMO DO OPERADOR SETA (->):
 *
 *   ptr->campo   é EXATAMENTE igual a   (*ptr).campo
 *
 *   Por quê -> existe? Legibilidade e precedência de operadores.
 *   (*ptr).campo tem um problema sutil: o operador . tem precedência
 *   maior que *, então SEM os parênteses ficaria *ptr.campo, que é
 *   "conteúdo do endereço guardado em ptr.campo" — ERRADO!
 *   O operador -> resolve isso de forma limpa.
 */
