import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;


public class PrincipalBiblioteca {
    private List<Livro> livros;
    private Scanner scanner ;

    public PrincipalBiblioteca(){
        livros = new ArrayList<>();
        scanner = new Scanner(System.in);
    }

    public void execCadastro(){
        Livro livro = new Livro();

        System.out.println("Digite o código do livro:");
        int condigo = scanner.nextInt();
        livro.setCondigo(condigo);
        scanner.nextLine();

        System.out.println("Digite o título do livro:");
        String nome = scanner.nextLine();
        livro.setTitulo(nome);
        scanner.nextLine();

        System.out.println("Digite o autor do livro:");
        String autor = scanner.nextLine();
        livro.setAutor(autor);
        scanner.nextLine();

        System.out.println("Digite a categoria do livro:");
        String categoria = scanner.nextLine();
        livro.setCategoria(categoria);
        livros.add(livro);

        System.out.println("Digite o preço do livro:");
        double preco = scanner.nextDouble();
        livro.setPreco(preco);
        livros.add(livro);

        livro.setDisponivel(true);
        livros.add(livro);
        System.out.println("Livro Cadastrado com sucesso!");

    }

    public void consultarLivro(){
        System.out.println("Digite o código do livro:");
        int condigo = scanner.nextInt();

        for(Livro livro : livros){
            if (livro.getCondigo() == condigo){
                livro.imprimir();
                return;
            }
        }
        System.out.println("Livro não encontrado");
    }

    public void emprestarLivro(){
        System.out.println("Digite o código do livro:");
        int condigo = scanner.nextInt();
        for(Livro livro : livros){
            if (livro.getCondigo() == condigo){
                livro.emprestar();
                return;
            }
        }
        System.out.println("Livro não encontrado");
    }

    public void devolverLivro(){
        System.out.println("Digite o código do livro");
        int condigo = scanner.nextInt();
        for(Livro livro : livros){
            if (livro.getCondigo() == condigo){
                livro.devolver();
                return;
            }
        }
        System.out.println("Livro não encontrado");
    }

    public void consultarDisponiveis(){
        System.out.println("======== LIVROS DISPONÍVEIS ========");
        for(Livro livro : livros){
            if (livro.isDisponivel()){
                livro.imprimir();
            }
        }
    }

    public void valorTotalAcervo(){
        double total = 0;
        for(Livro livro : livros){
            total += livro.getPreco();
        }
        System.out.println("Valor total do acervo: R$ " + total);
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        PrincipalBiblioteca principal = new PrincipalBiblioteca();
        int opcao = 0;
        do {
            System.out.println("x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-");
            System.out.println("      Sistema Biblioteca ");
            System.out.println("1. Cadastrar Livro");
            System.out.println("2. Consultar Livro");
            System.out.println("3. Emprestar Livro");
            System.out.println("4. Devolver Livro");
            System.out.println("5. Consultar livros disponíveis");
            System.out.println("6. Valor total do acervo");
            System.out.println("9. Sair");
            System.out.println("Digite sua opção:");
            opcao = scan.nextInt();

            switch (opcao) {
                case 1:
                    principal.execCadastro();
                    break;
                case 2:
                    principal.consultarLivro();
                    break;
                case 3:
                    principal.emprestarLivro();
                    break;
                case 4:
                    principal.devolverLivro();
                    break;
                case 5:
                    principal.consultarDisponiveis();
                    break;
                case 6:
                    principal.valorTotalAcervo();
                    break;
                case 9:
                    System.out.println("Sistema encerrado.");
                    break;
                default:
                    System.out.println("Opção invalida.");
            }

        }while (opcao != 9);

    }

}



