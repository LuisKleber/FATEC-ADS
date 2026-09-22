

public class Livro {
    private int condigo;
    private String titulo;
    private String autor;
    private String categoria;
    private double preco;
    private boolean disponivel;

    public int getCondigo() {
        return condigo;
    }

    public void setCondigo(int condigo) {
        this.condigo = condigo;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public String getAutor() {
        return autor;
    }

    public void setAutor(String autor) {
        this.autor = autor;
    }

    public String getCategoria() {
        return categoria;
    }

    public void setCategoria(String categoria) {
        this.categoria = categoria;
    }

    public double getPreco() {
        return preco;
    }

    public void setPreco(double preco) {
        this.preco = preco;
    }

    public boolean isDisponivel() {
        return disponivel;
    }

    public void setDisponivel(boolean disponivel) {
        this.disponivel = disponivel;
    }

    public void emprestar(){
        if  (disponivel==true){
             disponivel=false;
             System.out.println("Emprestado com sucesso!!");
    } else {
        System.out.println("O livro não está disponível para empréstimo.");
    }
}
    public void devolver(){
    if (!disponivel){
         disponivel=true;
        System.out.println("Devolução realizada com sucesso!!");
    } else {
        System.out.println("O livro já está disponível.");
    }
}

    public void imprimir() {
        System.out.println("---------------------------------");
        System.out.println("Código: " + condigo);
        System.out.println("Titulo: " + titulo);
        System.out.println("Autor: " + autor);
        System.out.println("Categoria: " + categoria);
        System.out.println("Preço: " + preco);
    if (disponivel) {
        System.out.println("Situação: Disponível");
    } else {
        System.out.println("Situação: Emprestado");
    }

        System.out.println("-------------------------------");
}

}