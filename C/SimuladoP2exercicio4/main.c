/*
 * EXERCÍCIO 4: Recursividade — Cálculo de Potência
 * ==================================================
 * Objetivo:
 *   Calcular base^exp de forma recursiva SEM usar <math.h>.
 *   O CASO BASE (critério de parada) DEVE ser a PRIMEIRA instrução.
 *
 * CONCEITOS-CHAVE:
 *   - Recursividade: função que chama a si mesma com um problema menor.
 *   - Caso Base: condição que PARA a recursão. Sem ele → stack overflow!
 *   - Caso Recursivo: reduz o problema (exp - 1) e combina o resultado.
 *   - Stack (Pilha): cada chamada de função empilha um "frame" na memória.
 *     Recursão profunda = muitos frames = risco de estouro da pilha.
 *
 * RACIOCÍNIO MATEMÁTICO:
 *   base^0 = 1                    ← Caso Base
 *   base^exp = base * base^(exp-1) ← Caso Recursivo
 *
 * VISUALIZAÇÃO DA PILHA para potencia_recursiva(2, 4):
 *   potencia(2, 4) = 2 * potencia(2, 3)
 *                        = 2 * potencia(2, 2)
 *                              = 2 * potencia(2, 1)
 *                                    = 2 * potencia(2, 0)
 *                                              = 1       ← CASO BASE
 *                                    = 2 * 1 = 2
 *                              = 2 * 2 = 4
 *                        = 2 * 4 = 8
 *   = 2 * 8 = 16 ✓
 */

#include <stdio.h>

/*
 * potencia_recursiva()
 * ---------------------
 * base: número a ser elevado
 * exp : expoente (inteiro não-negativo)
 * Retorna: base elevado a exp (long para suportar valores grandes)
 */
long potencia_recursiva(int base, int exp) {

    /* ─── CASO BASE ────────────────────────────────────────────────
     * Deve ser a PRIMEIRA instrução conforme exigência do professor.
     * Qualquer número elevado a 0 é igual a 1.
     * Este é o "freio" que impede a recursão infinita.
     * ──────────────────────────────────────────────────────────── */
    if (exp == 0) {
        return 1;
    }

    /* ─── CASO RECURSIVO ───────────────────────────────────────────
     * Reduzimos o expoente em 1 a cada chamada.
     * O resultado parcial é multiplicado pela base.
     * A recursão "desce" até o caso base e então "sobe" combinando.
     * ──────────────────────────────────────────────────────────── */
    return base * potencia_recursiva(base, exp - 1);
}

int main() {
    int base, exp;

    printf("=== Calculadora de Potencia Recursiva ===\n");
    printf("Base    : ");
    scanf("%d", &base);
    printf("Expoente: ");
    scanf("%d", &exp);

    /* Validação: este algoritmo não trata expoentes negativos */
    if (exp < 0) {
        printf("Erro: expoente deve ser >= 0 para este algoritmo.\n");
        return 1;
    }

    long resultado = potencia_recursiva(base, exp);

    printf("\n%d^%d = %ld\n", base, exp, resultado);

    /* Demonstração de casos extras para visualização */
    printf("\n--- Tabela de potencias de %d ---\n", base);
    for (int i = 0; i <= 8; i++) {
        printf("  %d^%d = %ld\n", base, i, potencia_recursiva(base, i));
    }

    return 0;
}

/*
 * POR QUE long E NÃO int?
 *   Potências crescem exponencialmente. 2^31 já estoura um int.
 *   long garante pelo menos 32 bits (geralmente 64 em sistemas modernos).
 *
 * ATENÇÃO: Para expoentes muito grandes (ex: 2^10000), mesmo long
 * estoura. Mas para fins acadêmicos, long é suficiente.
 */
