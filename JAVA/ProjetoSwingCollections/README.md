# Sistema de Academia e Fichas de Treino

**Disciplina:** Programação Orientada a Objetos — Prof. Me. Marcos Roberto de Moraes (Maromo)
**Instituição:** Fatec Mogi Mirim
**Tema escolhido:** 09 — Sistema de Academia e Fichas de Treino

## Dupla
| Nome                   | RA |
|------------------------|----|
| Luis Kleber de Arruda  | 1630482521037
| Priscila Maciel       | 1630482521042

## Descrição
Sistema em Java (Swing) que gerencia alunos de uma academia **inteiramente em memória** (`List<AlunoAcademia>`): cadastro, pesquisa, registro de frequência, suspensão/reativação por pendência, cálculo de IMC e listagem ordenada de alunos ativos.

## Arquitetura
```
src/
├── Main.java                              -> instancia TelaAcademia e chama setVisible(true)
├── model/AlunoAcademia.java               -> entidade (Comparable, equals, hashCode, toString)
├── interfaces/Avaliavel.java              -> contrato polimórfico (abstrato + default + static)
├── exceptions/MatriculaBloqueadaException -> Checked Exception (extends Exception)
└── view/TelaAcademia.java                 -> JFrame com JTextField, JButton, JTextArea, JOptionPane
```
- **AlunoAcademia** implementa `Comparable<AlunoAcademia>` (ordem natural por matrícula) e possui um `Comparator` estático para ordenar por mensalidade. `equals()`/`hashCode()` baseiam-se na matrícula.
- **Avaliavel** define `calcularIndiceMassaCorporal()`, o método `default classificarIMC()` e o método `static medidasValidas()`.
- **MatriculaBloqueadaException** é lançada ao registrar frequência de um aluno suspenso.
- **TelaAcademia** trata cliques com `ActionListener` e o fechamento da janela com `WindowListener`; erros de conversão (`NumberFormatException`) e regras de negócio são exibidos com `JOptionPane.showMessageDialog()`.

## Como executar
Requer JDK 11+.
```bash
javac -d out src/Main.java src/model/*.java src/interfaces/*.java src/exceptions/*.java src/view/*.java
java -cp out Main
```

## Histórico de prompts de IA
> Documentem aqui **todos** os prompts reais usados, as respostas obtidas e como refinaram o resultado.

### Prompt 1
**O que foi pedido:** Ajuda para fazer o trabalho prático de POO (PDF do enunciado anexado), com o tema 09 — Academia.
**Resposta obtida:** Estrutura de projeto com pacotes `model`, `interfaces`, `exceptions`, `view` e a classe `Main`, com código-base completo.
**Como refinamos:** _(descrevam o que testaram, ajustaram, mudaram de layout, regras etc.)_

