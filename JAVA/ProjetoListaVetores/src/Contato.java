/**
 * Representa um registro da "agenda" (um registro do arquivo simulado em disco).
 * A chave de pesquisa é o CPF.
 */
public class Contato {

    private String nome;
    private String endereco;
    private String cpf;
    private String telefone;
    private String email;

    public Contato(String nome, String endereco, String cpf, String telefone, String email) {
        this.nome = nome;
        this.endereco = endereco;
        this.cpf = cpf;
        this.telefone = telefone;
        this.email = email;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEndereco() {
        return endereco;
    }

    public void setEndereco(String endereco) {
        this.endereco = endereco;
    }

    public String getCpf() {
        return cpf;
    }

    public void setCpf(String cpf) {
        this.cpf = cpf;
    }

    public String getTelefone() {
        return telefone;
    }

    public void setTelefone(String telefone) {
        this.telefone = telefone;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    /** Retorna apenas os dígitos do CPF, para comparar "123.456.789-09" com "12345678909". */
    public static String somenteDigitos(String cpf) {
        return cpf == null ? "" : cpf.replaceAll("\\D", "");
    }

    @Override
    public String toString() {
        return "Nome:     " + nome + "\n"
             + "Endereço: " + endereco + "\n"
             + "CPF:      " + cpf + "\n"
             + "Telefone: " + telefone + "\n"
             + "E-mail:   " + email;
    }
}
