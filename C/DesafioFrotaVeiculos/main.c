
/*
 * main.c — Ponto de Entrada do Sistema CargoTrack
 * =================================================
 * Responsabilidade ÚNICA deste arquivo:
 *   - Definir o vetor global `frota`
 *   - Exibir o menu interativo
 *   - Chamar as funções corretas de veiculo.c
 *
 * POR QUE SEPARAR EM main.c + veiculo.c + veiculo.h?
 *   ┌──────────────┬────────────────────────────────────────┐
 *   │ veiculo.h    │ "Contrato": tipos e protótipos         │
 *   │ veiculo.c    │ "Implementação": lógica das funções    │
 *   │ main.c       │ "Orquestrador": menu e fluxo principal │
 *   └──────────────┴────────────────────────────────────────┘
 *   Esta separação é o padrão em projetos C profissionais.
 *   No CLion, o CMakeLists.txt compila os dois .c juntos.
 */

#include <stdio.h>
#include <stdlib.h>   /* system("clear") / system("cls") */
#include "contrato.h"  /* Importa tudo que definimos */

/*
 * DEFINIÇÃO DO VETOR GLOBAL
 * --------------------------
 * "Veiculo *frota[MAX_VEICULOS]" declara um vetor de MAX_VEICULOS
 * ponteiros para Veiculo.
 *
 * Cada posição começa como NULL (variáveis globais em C são zeradas).
 * Quando cadastramos um veículo, malloc() aloca memória e guardamos
 * o endereço retornado nessa posição do vetor.
 *
 * VISUALIZAÇÃO:
 *   frota[0] ──► NULL          (vazio)
 *   frota[1] ──► Veiculo {...} (cadastrado — apontando para a HEAP)
 *   frota[2] ──► NULL          (vazio)
 *   ...
 *
 * Por que GLOBAL?
 *   Todas as funções em veiculo.c precisam acessar este vetor.
 *   O "extern Veiculo *frota[]" em veiculo.h avisa o compilador
 *   que a variável existe aqui (main.c).
 */
Veiculo *frota[MAX_VEICULOS];

/*
 * exibir_menu()
 * --------------
 * Exibe as opções disponíveis. Separado em função para não poluir main().
 */
void exibir_menu(void) {
    printf("\n+----------------------------------+\n");
    printf("|     CargoTrack v1.0              |\n");
    printf("+----------------------------------+\n");
    printf("|  1. Cadastrar veiculo            |\n");
    printf("|  2. Listar frota completa        |\n");
    printf("|  3. Buscar por placa             |\n");
    printf("|  4. Atualizar dados              |\n");
    printf("|  0. Sair                         |\n");
    printf("+----------------------------------+\n");
    printf("Opcao: ");
}

/*
 * main()
 * -------
 * Loop principal do programa.
 * Lê a opção do usuário e despacha para a função correta.
 *
 * do { ... } while (opcao != 0):
 *   Garante que o menu seja exibido ao menos UMA VEZ antes de verificar
 *   a condição de saída (diferente do while que verifica antes).
 */
int main(void) {
    int opcao;

    /* ── Inicialização obrigatória ─────────────────────────────── */
    iniciar_frota();

    do {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_veiculo();
                break;

            case 2:
                listar_frota_completa();
                break;

            case 3:
                buscar_veiculo_por_placa();
                break;

            case 4:
                atualizar_dados_veiculo();
                break;

            case 0:
                printf("\n[✓] Encerrando CargoTrack. Ate logo!\n");
                break;

            default:
                printf("\n[✗] Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    /*
     * BOAS PRÁTICAS: liberar a memória alocada antes de encerrar.
     * Em programas reais isso é obrigatório para evitar memory leaks.
     * Aqui o SO recupera a memória ao fechar, mas o hábito é importante.
     */
    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (frota[i] != NULL) {
            free(frota[i]);
            frota[i] = NULL;
        }
    }

    return 0;
}
