import java.util.Scanner;

/**
 * Programa principal: menu para manipular a lista de contatos.
 */
public class Main {

    private static final Scanner entrada = new Scanner(System.in);
    private static final ListaContatos lista = new ListaContatos();

    public static void main(String[] args) {
        int opcao;
        do {
            exibirMenu();
            opcao = lerOpcao();
            System.out.println();

            switch (opcao) {
                case 1 -> adicionar();
                case 2 -> excluir();
                case 3 -> alterar();
                case 4 -> imprimir();
                case 5 -> imprimirTodos();
                case 6 -> ordenar();
                case 7 -> System.out.println("Encerrando o sistema...");
                default -> System.out.println("Opção inválida!");
            }
        } while (opcao != 7);
    }

    private static void exibirMenu() {
        System.out.println();
        System.out.println("===== MENU =====");
        System.out.println("1. Adicionar");
        System.out.println("2. Excluir");
        System.out.println("3. Alterar");
        System.out.println("4. Imprimir");
        System.out.println("5. Imprimir todos");
        System.out.println("6. Ordenar");
        System.out.println("7. Sair");
        System.out.print("Escolha uma opção: ");
    }

    private static int lerOpcao() {
        try {
            return Integer.parseInt(entrada.nextLine().trim());
        } catch (NumberFormatException e) {
            return -1;
        }
    }

    private static String lerTexto(String rotulo) {
        System.out.print(rotulo);
        return entrada.nextLine().trim();
    }

    /** Pede o CPF até o usuário digitar algo (CPF vazio não é aceito como chave). */
    private static String lerCpf() {
        String cpf;
        do {
            cpf = lerTexto("CPF: ");
            if (Contato.somenteDigitos(cpf).isEmpty()) {
                System.out.println("Informe um CPF válido (apenas números ou no formato 000.000.000-00).");
            }
        } while (Contato.somenteDigitos(cpf).isEmpty());
        return cpf;
    }

    // 1. Adicionar: pede o CPF, verifica se já existe e, senão, pede os demais dados e grava.
    private static void adicionar() {
        String cpf = lerCpf();
        if (lista.contem(cpf)) {
            System.out.println("CPF já cadastrado");
            return;
        }
        String nome = lerTexto("Nome: ");
        String endereco = lerTexto("Endereço: ");
        String telefone = lerTexto("Telefone: ");
        String email = lerTexto("E-mail: ");

        lista.adicionar(new Contato(nome, endereco, cpf, telefone, email));
        System.out.println("Contato cadastrado com sucesso!");
    }

    // 2. Excluir: pede o CPF e exclui se existir; caso contrário ignora, sem mensagem.
    private static void excluir() {
        String cpf = lerCpf();
        lista.excluir(cpf);
    }

    // 3. Alterar: mostra os campos atuais; ENTER mantém o valor.
    private static void alterar() {
        String cpf = lerCpf();
        Contato contato = lista.buscar(cpf);
        if (contato == null) {
            System.out.println("CPF não cadastrado");
            return;
        }

        System.out.println("Dados atuais:");
        System.out.println(contato);
        System.out.println();
        System.out.println("Digite os novos valores (ENTER para manter o atual):");

        String nome = lerTexto("Nome [" + contato.getNome() + "]: ");
        if (!nome.isEmpty()) {
            contato.setNome(nome);
        }
        String endereco = lerTexto("Endereço [" + contato.getEndereco() + "]: ");
        if (!endereco.isEmpty()) {
            contato.setEndereco(endereco);
        }
        String telefone = lerTexto("Telefone [" + contato.getTelefone() + "]: ");
        if (!telefone.isEmpty()) {
            contato.setTelefone(telefone);
        }
        String email = lerTexto("E-mail [" + contato.getEmail() + "]: ");
        if (!email.isEmpty()) {
            contato.setEmail(email);
        }
        System.out.println("Contato alterado com sucesso!");
    }

    // 4. Imprimir: pede o CPF e mostra todos os campos, ou "CPF não cadastrado".
    private static void imprimir() {
        String cpf = lerCpf();
        Contato contato = lista.buscar(cpf);
        if (contato == null) {
            System.out.println("CPF não cadastrado");
        } else {
            System.out.println(contato);
        }
    }

    // 5. Imprimir todos os elementos cadastrados.
    private static void imprimirTodos() {
        if (lista.estaVazia()) {
            System.out.println("Nenhum contato cadastrado.");
            return;
        }
        for (int i = 0; i < lista.getTamanho(); i++) {
            System.out.println("--- Contato " + (i + 1) + " ---");
            System.out.println(lista.get(i));
            System.out.println();
        }
    }

    // 6. Ordenar por nome.
    private static void ordenar() {
        lista.ordenarPorNome();
        System.out.println("Lista ordenada por nome.");
    }
}
