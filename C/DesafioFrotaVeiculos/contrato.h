/*
 * veiculo.h — Definições centrais do sistema CargoTrack
 * =======================================================
 * Este arquivo de cabeçalho (header) contém:
 *   - Constantes de pré-processador (#define)
 *   - Definição da struct Veiculo
 *   - Protótipos de todas as funções
 *
 * POR QUE UM ARQUIVO .h?
 *   Separar a definição do tipo em um .h permite que múltiplos
 *   arquivos .c "enxerguem" o mesmo tipo sem duplicar código.
 *   O #include "veiculo.h" faz o compilador inserir este conteúdo
 *   no ponto da inclusão (substituição textual, como #define).
 *
 * GUARD DE INCLUSÃO (#ifndef / #define / #endif):
 *   Evita que o compilador processe este arquivo mais de uma vez
 *   caso ele seja incluído por múltiplos .c. Sem o guard,
 *   ocorreria erro de "redefinição de tipo".
 */

#ifndef CONTRATO_H
#define CONTRATO_H

/* -------------------------------------------------------
 * CONSTANTES DE CONFIGURAÇÃO
 * Altere apenas aqui para ajustar o sistema inteiro.
 * ------------------------------------------------------- */
#define MAX_VEICULOS 10   /* Capacidade máxima da frota */
#define TAM_PLACA    10   /* "ABC1D23" + '\0' com margem */
#define TAM_MODELO   50
#define TAM_MOTORISTA 60

/* -------------------------------------------------------
 * STRUCT VEICULO
 * Modela um veículo utilitário da frota CargoTrack.
 *
 * Por que double para capacidade_carga?
 *   double tem precisão de ~15 dígitos decimais, adequado para
 *   valores como 1250.75 kg sem perda de precisão.
 *
 * Por que int para status?
 *   Inteiros são eficientes para flags binários.
 *   Usaremos a convenção: 1 = Disponível, 0 = Em Rota.
 * ------------------------------------------------------- */
typedef struct {
    char   placa[TAM_PLACA];         /* Identificador único: "ABC1D23" */
    char   modelo[TAM_MODELO];       /* Ex: "Mercedes Sprinter" */
    char   motorista[TAM_MOTORISTA]; /* Nome do motorista responsável */
    double capacidade_carga;         /* Capacidade em kg */
    int    status;                   /* 1 = Disponível | 0 = Em Rota */
} Veiculo;

/*
 * POR QUE typedef struct { ... } Veiculo;  EM VEZ DE  struct Veiculo { ... };?
 *
 * Sem typedef: toda declaração de variável exige a palavra "struct":
 *   struct Veiculo *v;   ← verboso
 *
 * Com typedef: criamos um alias "Veiculo" para o tipo, então:
 *   Veiculo *v;          ← mais limpo, padrão em C moderno
 */

/* -------------------------------------------------------
 * VETOR GLOBAL DE PONTEIROS (declarado como extern)
 *
 * "extern" diz: "esta variável EXISTE em outro .c (main.c),
 *  mas quero referenciá-la aqui também."
 * A definição real (com memória reservada) está em main.c.
 * ------------------------------------------------------- */
extern Veiculo *frota[MAX_VEICULOS];

/* -------------------------------------------------------
 * PROTÓTIPOS DAS FUNÇÕES
 * O compilador precisa conhecer a assinatura antes do uso.
 * ------------------------------------------------------- */
void iniciar_frota(void);
void cadastrar_veiculo(void);
void imprimir_veiculo(int pos);
void listar_frota_completa(void);
void buscar_veiculo_por_placa(void);
void atualizar_dados_veiculo(void);

/* Utilitários internos */
int  encontrar_posicao_livre(void);
int  buscar_indice_por_placa(const char *placa);
void limpar_newline(char *str);
void exibir_menu(void);

#endif  /* VEICULO_H */
