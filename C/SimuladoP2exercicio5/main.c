/*
 * EXERCÍCIO 5: Passagem por Referência e Ponteiros
 * ==================================================
 * Objetivo:
 *   Implementar void inverter_e_menor(int *a, int *b, int *menor) que:
 *     1. Identifica o MENOR valor ANTES de inverter (guarda em *menor).
 *     2. Inverte os valores de *a e *b usando variável temporária.
 *
 * CONCEITOS-CHAVE:
 *   - Passagem por VALOR: a função recebe uma CÓPIA. Mudanças não afetam o original.
 *   - Passagem por REFERÊNCIA (ponteiros em C): a função recebe o ENDEREÇO da variável.
 *     Mudanças via *ptr afetam diretamente a variável original.
 *   - Operador &: obtém o endereço de uma variável.  ex: &x → endereço de x
 *   - Operador *: acessa o conteúdo do endereço (dereference). ex: *a → valor em &a
 *
 * ORDEM DAS OPERAÇÕES (crítica!):
 *   O enunciado exige que *menor seja preenchido ANTES da troca.
 *   Se invertermos primeiro, perdemos a informação original.
 */

#include <stdio.h>

/*
 * inverter_e_menor()
 * ------------------
 * int *a     → endereço do primeiro valor  (passagem por referência)
 * int *b     → endereço do segundo valor   (passagem por referência)
 * int *menor → endereço onde guardar o menor valor antes da troca
 */
void inverter_e_menor(int *a, int *b, int *menor) {

    /* ─── PASSO 1: Identificar o MENOR antes de qualquer troca ────
     * *a e *b acessam os valores originais nos endereços recebidos.
     * Gravamos o menor DIRETAMENTE no endereço apontado por *menor.
     * ──────────────────────────────────────────────────────────── */
    if (*a < *b) {
        *menor = *a;   /* *a é menor: grava o valor de a no endereço de menor */
    } else {
        *menor = *b;   /* *b é menor (ou iguais): grava o valor de b */
    }

    /* ─── PASSO 2: Inverter os valores com variável temporária ────
     * A troca direta sem temp NÃO funciona:
     *   *a = *b;  ← perde o valor original de *a!
     *   *b = *a;  ← agora *a já é *b, ambos iguais. Errado!
     *
     * Com temp:
     *   temp = *a  → salva o valor original de a
     *   *a   = *b  → a recebe o valor de b
     *   *b   = temp → b recebe o valor original de a
     * ──────────────────────────────────────────────────────────── */
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20, m;

    printf("=== Antes da chamada ===\n");
    printf("  x = %d\n", x);
    printf("  y = %d\n", y);

    /*
     * Passamos os ENDEREÇOS com o operador &
     * A função vai manipular diretamente as variáveis x, y e m
     * que estão na memória do main().
     */
    inverter_e_menor(&x, &y, &m);

    printf("\n=== Apos a chamada ===\n");
    printf("  x = %d  (era 10, agora tem o valor de y)\n", x);
    printf("  y = %d  (era 20, agora tem o valor de x)\n", y);
    printf("  m = %d  (menor dos dois ANTES da troca)\n", m);

    /* ─── Teste com outros valores (usuário) ─────────────────── */
    printf("\n=== Teste interativo ===\n");
    int a, b, menor;
    printf("Digite o primeiro valor : ");
    scanf("%d", &a);
    printf("Digite o segundo valor  : ");
    scanf("%d", &b);

    inverter_e_menor(&a, &b, &menor);

    printf("\nApos inverter:\n");
    printf("  Primeiro valor agora: %d\n", a);
    printf("  Segundo valor agora : %d\n", b);
    printf("  Menor (antes da troca): %d\n", menor);

    return 0;
}

/*
 * VISUALIZAÇÃO NA MEMÓRIA (exemplo com x=10, y=20):
 *
 *   Endereço  │ Variável │ Valor
 *   ──────────┼──────────┼──────
 *   0x1000    │   x      │  10    ← &x passado como *a
 *   0x1004    │   y      │  20    ← &y passado como *b
 *   0x1008    │   m      │   ?    ← &m passado como *menor
 *
 *   Dentro da função, *a acessa 0x1000, *b acessa 0x1004, etc.
 *   Ao escrever *a = *b, gravamos 20 no endereço 0x1000 (o x original!).
 */
