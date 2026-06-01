/*
 * EXERCÍCIO 3: Modularização e Escopo de Funções — Sistema de IMC
 * ================================================================
 * Objetivo:
 *   1. main()            → coleta peso e altura do usuário.
 *   2. calcular_imc()    → função com retorno: realiza o cálculo matemático.
 *   3. imprimir_resultado() → procedimento void: classifica e exibe a categoria.
 *
 * CONCEITOS-CHAVE:
 *   - Protótipos (declarações antecipadas): informam ao compilador a assinatura
 *     das funções antes de seu uso em main(). Obrigatório quando a definição
 *     aparece após a chamada no arquivo.
 *   - Função vs Procedimento: função tem retorno (float); procedimento é void.
 *   - IMC = peso / (altura * altura)   [kg/m²]
 */

#include <stdio.h>

/* -------------------------------------------------------
 * PROTÓTIPOS (declarações antecipadas)
 * O compilador lê de cima para baixo; sem isso, ele não
 * conhece a assinatura das funções quando chega no main().
 * ------------------------------------------------------- */
float calcular_imc(float p, float a);
void  imprimir_resultado(float imc);

/* -------------------------------------------------------
 * main(): ORQUESTRADOR
 * Responsabilidade única: coletar dados e coordenar chamadas.
 * NÃO faz cálculo nem impressão de resultado — delega isso.
 * ------------------------------------------------------- */
int main() {
    float peso, altura, imc;

    printf("=== Sistema de Analise de IMC ===\n");
    printf("Informe seu peso (kg): ");
    scanf("%f", &peso);

    printf("Informe sua altura (m): ");
    scanf("%f", &altura);

    /* Valida entradas básicas antes de calcular */
    if (peso <= 0 || altura <= 0) {
        printf("Erro: peso e altura devem ser valores positivos.\n");
        return 1;   /* Código de saída diferente de 0 indica erro */
    }

    /* Delega o cálculo para a função especializada */
    imc = calcular_imc(peso, altura);

    printf("\nSeu IMC calculado: %.2f kg/m²\n", imc);

    /* Delega a classificação e impressão para o procedimento */
    imprimir_resultado(imc);

    return 0;
}

/* -------------------------------------------------------
 * calcular_imc()
 * FUNÇÃO (tem retorno float): realiza APENAS o cálculo.
 * Parâmetros: p = peso (kg), a = altura (m)
 * Retorna: o valor numérico do IMC.
 *
 * Fórmula: IMC = p / (a²)
 * ------------------------------------------------------- */
float calcular_imc(float p, float a) {
    return p / (a * a);
}

/* -------------------------------------------------------
 * imprimir_resultado()
 * PROCEDIMENTO (void): recebe o IMC já calculado e exibe
 * a classificação segundo tabela da OMS.
 * NÃO faz cálculo, NÃO lê dados — só classifica e imprime.
 * ------------------------------------------------------- */
void imprimir_resultado(float imc) {
    printf("Classificacao: ");

    if (imc < 18.5f) {
        printf("Abaixo do peso\n");
    } else if (imc < 25.0f) {
        printf("Peso normal\n");
    } else if (imc < 30.0f) {
        printf("Sobrepeso\n");
    } else if (imc < 35.0f) {
        printf("Obesidade Grau I\n");
    } else if (imc < 40.0f) {
        printf("Obesidade Grau II\n");
    } else {
        printf("Obesidade Grau III (Morbida)\n");
    }
}

/*
 * EXEMPLO DE EXECUÇÃO:
 *   Peso: 70 kg | Altura: 1.75 m
 *   IMC = 70 / (1.75 * 1.75) = 70 / 3.0625 ≈ 22.86
 *   Classificação: Peso normal
 */
