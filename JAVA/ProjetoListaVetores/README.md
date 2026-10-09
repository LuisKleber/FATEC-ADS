# Lista de Contatos baseada em Vetores (Java)

Projeto da disciplina **Estrutura de Dados** (Aula 05 – Projeto Listas baseadas em Vetores), FATEC Mogi Mirim.

Sistema em console que usa uma **lista implementada sobre um vetor (array)** para simular um arquivo em disco, armazenando contatos com:

- Nome
- Endereço
- CPF (chave de pesquisa, sem repetição)
- Telefone
- E-mail

## Menu

| Opção | Descrição |
|-------|-----------|
| 1. Adicionar | Pede o CPF. Se já existir, mostra `CPF já cadastrado`; senão pede os demais dados e grava. |
| 2. Excluir | Pede o CPF e exclui se existir; se não existir, ignora sem mensagem. |
| 3. Alterar | Pede o CPF (`CPF não cadastrado` se não existir). Mostra cada campo e permite digitar o novo valor; `ENTER` mantém o atual. |
| 4. Imprimir | Pede o CPF e mostra todos os campos, ou `CPF não cadastrado`. |
| 5. Imprimir todos | Mostra todos os contatos cadastrados. |
| 6. Ordenar | Ordena a lista por nome (ignora maiúsculas/minúsculas e acentos). |
| 7. Sair | Encerra o programa. |

## Estrutura

```
src/
├── Contato.java        # Entidade (registro)
├── ListaContatos.java  # Lista baseada em vetor: adicionar, excluir, buscar, ordenar
└── Main.java           # Menu e interação com o usuário
```

### Decisões de implementação

- O vetor interno começa com 10 posições e **dobra de tamanho** automaticamente quando enche.
- A **exclusão** desloca os elementos seguintes uma posição para a esquerda.
- A **busca** é sequencial pelo CPF; a comparação usa apenas os dígitos, então `123.456.789-09` e `12345678909` são o mesmo CPF.
- A **ordenação** usa *insertion sort* implementado manualmente, com `Collator` pt-BR para ordem alfabética correta com acentos.
- Não foi usado `ArrayList`, já que o objetivo da aula é implementar a lista sobre vetor.

## Como executar

Requer **JDK 17 ou superior**.

```bash
# Compilar
javac -encoding UTF-8 -d out src/*.java

# Executar
java -cp out Main
```

> No Windows, se os acentos aparecerem errados no terminal, rode `chcp 65001` antes de executar.

## Autor

Luís Arruda — Análise e Desenvolvimento de Sistemas, FATEC Mogi Mirim.
