/*
 * veiculo.c — Implementação das funções do sistema CargoTrack
 * =============================================================
 * Este arquivo contém a lógica de todas as operações da frota.
 *
 * SEPARAÇÃO DE RESPONSABILIDADES:
 *   veiculo.h  → "O QUE existe" (tipos, protótipos, constantes)
 *   veiculo.c  → "COMO funciona" (implementação das funções)
 *   main.c     → "QUANDO usar" (menu, fluxo do programa)
 */

#include <stdio.h>
#include <stdlib.h>   /* malloc(), free() */
#include <string.h>   /* strcmp(), strcpy(), strlen() */
#include "contrato.h"  /* Nosso próprio header (aspas = pasta local) */

/* ═══════════════════════════════════════════════════════════════
 * UTILITÁRIOS INTERNOS (funções auxiliares)
 * ═══════════════════════════════════════════════════════════════ */

/*
 * limpar_newline()
 * -----------------
 * O fgets() inclui o '\n' do Enter na string lida.
 * Esta função localiza e substitui esse '\n' por '\0'.
 *
 * strcspn(str, "\n") retorna o índice do primeiro '\n' encontrado.
 * Se não houver '\n' (string preencheu o buffer), retorna strlen(str),
 * e str[strlen] = '\0' apenas reescreve o terminador — sem dano.
 */
void limpar_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/*
 * encontrar_posicao_livre()
 * --------------------------
 * Percorre o vetor frota[] e retorna o índice da primeira posição NULL.
 * Retorna -1 se o vetor estiver cheio.
 *
 * Por que verificar NULL?
 *   iniciar_frota() preenche todas as posições com NULL.
 *   Quando cadastramos, alocamos memória e gravamos o endereço.
 *   NULL = posição vazia; ponteiro válido = posição ocupada.
 */
int encontrar_posicao_livre(void) {
    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (frota[i] == NULL) {
            return i;
        }
    }
    return -1;  /* Frota cheia */
}

/*
 * buscar_indice_por_placa()
 * --------------------------
 * Recebe uma string com a placa e retorna o índice no vetor.
 * Retorna -1 se não encontrado.
 *
 * strcmp(a, b):
 *   Compara strings letra a letra.
 *   Retorna 0 se forem IGUAIS — não podemos usar == para strings em C!
 *   (== compara endereços de memória, não conteúdo)
 */
int buscar_indice_por_placa(const char *placa) {
    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (frota[i] != NULL && strcmp(frota[i]->placa, placa) == 0) {
            return i;
        }
    }
    return -1;
}

/* ═══════════════════════════════════════════════════════════════
 * FUNÇÕES PRINCIPAIS DO SISTEMA
 * ═══════════════════════════════════════════════════════════════ */

/*
 * iniciar_frota()
 * ----------------
 * Inicializa TODAS as posições do vetor com NULL.
 *
 * POR QUE ISSO É OBRIGATÓRIO?
 *   Em C, variáveis globais de ponteiros são inicializadas com NULL
 *   automaticamente, mas tornar explícito é boa prática.
 *   Mais importante: se o programa fosse reinicializado sem isso,
 *   ponteiros "lixo" causariam comportamento indefinido ao serem
 *   dereferenciados (acesso a memória inválida = crash).
 *
 * Complexidade: O(n) — percorre MAX_VEICULOS posições uma vez.
 */
void iniciar_frota(void) {
    for (int i = 0; i < MAX_VEICULOS; i++) {
        frota[i] = NULL;
    }
    printf("\n[✓] Sistema CargoTrack iniciado. Capacidade: %d veiculos.\n",
           MAX_VEICULOS);
}

/*
 * cadastrar_veiculo()
 * --------------------
 * 1. Verifica se há espaço (posição NULL disponível).
 * 2. Aloca dinamicamente memória para um novo Veiculo.
 * 3. Lê os dados do usuário com fgets (seguro) e scanf.
 * 4. Armazena o ponteiro no vetor.
 *
 * ALOCAÇÃO DINÂMICA (malloc):
 *   malloc(sizeof(Veiculo)) → reserva na HEAP exatamente
 *   o número de bytes que a struct Veiculo ocupa.
 *   Retorna um void* que fazemos cast para Veiculo*.
 *   Se malloc retornar NULL → sem memória disponível (tratar!).
 *
 * DIFERENÇA HEAP vs STACK:
 *   Stack: automático, liberado ao sair da função. Não serve para
 *          guardar dados que precisam persistir além da função.
 *   Heap:  manual (malloc/free), persiste até free() ser chamado.
 *          Por isso usamos heap aqui — o veículo deve existir enquanto
 *          o programa rodar, não só enquanto cadastrar_veiculo() executa.
 */
void cadastrar_veiculo(void) {
    int pos = encontrar_posicao_livre();

    if (pos == -1) {
        printf("\n[✗] Frota cheia! Maximo de %d veiculos atingido.\n",
               MAX_VEICULOS);
        return;
    }

    /* ── Alocação dinâmica ─────────────────────────────────────── */
    frota[pos] = (Veiculo *) malloc(sizeof(Veiculo));

    if (frota[pos] == NULL) {
        /* malloc retorna NULL se o sistema não tiver memória disponível */
        printf("\n[✗] Erro critico: falha na alocacao de memoria.\n");
        return;
    }

    printf("\n=== Cadastro de Veiculo (Posicao %d) ===\n", pos);

    /* Limpa o buffer do stdin antes do fgets
     * Necessário quando um scanf anterior deixou '\n' no buffer */
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    /* ── Leitura da Placa ──────────────────────────────────────── */
    printf("Placa (ex: ABC1D23): ");
    fgets(frota[pos]->placa, TAM_PLACA, stdin);
    limpar_newline(frota[pos]->placa);

    /* Verifica se a placa já existe (unicidade) */
    if (buscar_indice_por_placa(frota[pos]->placa) != pos) {
        printf("[✗] Placa '%s' ja cadastrada!\n", frota[pos]->placa);
        free(frota[pos]);   /* Libera a memória que acabamos de alocar */
        frota[pos] = NULL;  /* Marca posição como livre novamente */
        return;
    }

    /* ── Leitura do Modelo ─────────────────────────────────────── */
    printf("Modelo: ");
    fgets(frota[pos]->modelo, TAM_MODELO, stdin);
    limpar_newline(frota[pos]->modelo);

    /* ── Leitura do Motorista ──────────────────────────────────── */
    printf("Motorista: ");
    fgets(frota[pos]->motorista, TAM_MOTORISTA, stdin);
    limpar_newline(frota[pos]->motorista);

    /* ── Leitura da Capacidade de Carga ───────────────────────── */
    printf("Capacidade de carga (kg): ");
    scanf("%lf", &frota[pos]->capacidade_carga);
    /*
     * %lf para double com scanf (diferente de printf que usa %f para ambos)
     * &frota[pos]->capacidade_carga:
     *   frota[pos] é um Veiculo*
     *   frota[pos]->capacidade_carga acessa o campo via ponteiro
     *   & pega o endereço desse campo para o scanf gravar nele
     */

    /* ── Leitura do Status ─────────────────────────────────────── */
    printf("Status (1 = Disponivel / 0 = Em Rota): ");
    scanf("%d", &frota[pos]->status);

    printf("\n[✓] Veiculo '%s' cadastrado com sucesso na posicao %d!\n",
           frota[pos]->placa, pos);
}

/*
 * imprimir_veiculo()
 * -------------------
 * Exibe os dados formatados de um único veículo na posição `pos`.
 * Antes de acessar, verifica se frota[pos] != NULL (segurança).
 *
 * O operador ternário  (condição ? valor_se_true : valor_se_false)
 * é usado para exibir o status de forma legível.
 */
void imprimir_veiculo(int pos) {
    if (pos < 0 || pos >= MAX_VEICULOS || frota[pos] == NULL) {
        printf("  [vazio]\n");
        return;
    }

    printf("  +-------------------------------------+\n");
    printf("  | Posicao   : %-3d                     |\n", pos);
    printf("  | Placa     : %-28s|\n", frota[pos]->placa);
    printf("  | Modelo    : %-28s|\n", frota[pos]->modelo);
    printf("  | Motorista : %-28s|\n", frota[pos]->motorista);
    printf("  | Capacidade: %-6.2f kg                |\n", frota[pos]->capacidade_carga);
    printf("  | Status    : %-28s|\n",
           frota[pos]->status == 1 ? "Disponivel" : "Em Rota");
    printf("  +-------------------------------------+\n");
}

/*
 * listar_frota_completa()
 * ------------------------
 * Percorre o vetor inteiro e chama imprimir_veiculo() para cada posição.
 * Conta quantos veículos estão cadastrados para exibir no cabeçalho.
 */
void listar_frota_completa(void) {
    int total = 0;

    /* Conta veículos cadastrados */
    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (frota[i] != NULL) total++;
    }

    printf("\n=== Frota CargoTrack (%d/%d veiculos) ===\n",
           total, MAX_VEICULOS);

    if (total == 0) {
        printf("  Nenhum veiculo cadastrado.\n");
        return;
    }

    for (int i = 0; i < MAX_VEICULOS; i++) {
        if (frota[i] != NULL) {
            imprimir_veiculo(i);
        }
    }
}

/*
 * buscar_veiculo_por_placa()
 * ---------------------------
 * Lê uma placa do usuário e usa buscar_indice_por_placa() para encontrar.
 *
 * DETALHE: strcmp faz comparação case-sensitive.
 * "ABC1D23" != "abc1d23" — informe ao usuário para usar maiúsculas.
 */
void buscar_veiculo_por_placa(void) {
    char placa_busca[TAM_PLACA];

    printf("\n=== Busca por Placa ===\n");
    printf("Digite a placa (maiusculas, ex: ABC1D23): ");

    /* Limpa buffer antes do fgets */
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    fgets(placa_busca, TAM_PLACA, stdin);
    limpar_newline(placa_busca);

    int idx = buscar_indice_por_placa(placa_busca);

    if (idx == -1) {
        printf("\n[Erro] Veiculo com placa '%s' nao encontrado.\n", placa_busca);
    } else {
        printf("\n[Ok] Veiculo encontrado:\n");
        imprimir_veiculo(idx);
    }
}

/*
 * atualizar_dados_veiculo()
 * --------------------------
 * Permite editar motorista, capacidade e status de um veículo existente.
 *
 * LÓGICA DO "MANTER DADO ANTERIOR":
 *   Para strings: se o usuário pressionar ENTER sem digitar nada,
 *     fgets lê apenas "\n". Após limpar_newline(), o buffer fica "".
 *     Se strlen(buffer) == 0, o campo não é atualizado.
 *
 *   Para números: se o usuário digitar -1, o campo não é atualizado.
 *
 * POR QUE NÃO PERMITIR ALTERAR PLACA E MODELO?
 *   Placa é identificador único — alterá-la poderia causar duplicatas.
 *   Modelo é um dado fixo do veículo físico.
 *   Apenas dados operacionais (motorista, carga, status) mudam.
 */
void atualizar_dados_veiculo(void) {
    char placa_busca[TAM_PLACA];
    char buffer[TAM_MOTORISTA];

    printf("\n=== Atualizacao de Dados ===\n");
    printf("Placa do veiculo a atualizar: ");

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    fgets(placa_busca, TAM_PLACA, stdin);
    limpar_newline(placa_busca);

    int idx = buscar_indice_por_placa(placa_busca);

    if (idx == -1) {
        printf("\n[✗] Veiculo '%s' nao encontrado.\n", placa_busca);
        return;
    }

    printf("\n[Dados atuais do veiculo]\n");
    imprimir_veiculo(idx);
    printf("\n[Pressione ENTER para manter o dado atual]\n");

    /* ── Atualiza Motorista ────────────────────────────────────── */
    printf("Novo motorista [atual: %s]: ", frota[idx]->motorista);
    fgets(buffer, TAM_MOTORISTA, stdin);
    limpar_newline(buffer);
    if (strlen(buffer) > 0) {
        strcpy(frota[idx]->motorista, buffer);
        /* strcpy(destino, origem): copia a string incluindo o '\0' */
    }

    /* ── Atualiza Capacidade ───────────────────────────────────── */
    double nova_capacidade;
    printf("Nova capacidade em kg [atual: %.2f | -1 para manter]: ",
           frota[idx]->capacidade_carga);
    scanf("%lf", &nova_capacidade);
    if (nova_capacidade != -1) {
        frota[idx]->capacidade_carga = nova_capacidade;
    }

    /* ── Atualiza Status ───────────────────────────────────────── */
    int novo_status;
    printf("Novo status (1=Disponível / 0=Em Rota) [atual: %d | -1 para manter]: ",
           frota[idx]->status);
    scanf("%d", &novo_status);
    if (novo_status != -1) {
        frota[idx]->status = novo_status;
    }

    printf("\n[✓] Veiculo atualizado com sucesso!\n");
    imprimir_veiculo(idx);
}
