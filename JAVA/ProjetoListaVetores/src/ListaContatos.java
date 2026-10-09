import java.text.Collator;
import java.util.Locale;

/**
 * Lista baseada em vetor (array) que simula um arquivo em disco.
 *
 * O vetor interno cresce automaticamente quando fica cheio. A chave de pesquisa
 * é o CPF, e não é permitido cadastrar dois CPFs iguais.
 */
public class ListaContatos {

    private static final int CAPACIDADE_INICIAL = 10;

    private Contato[] dados;
    private int tamanho;

    public ListaContatos() {
        dados = new Contato[CAPACIDADE_INICIAL];
        tamanho = 0;
    }

    public int getTamanho() {
        return tamanho;
    }

    public boolean estaVazia() {
        return tamanho == 0;
    }

    public Contato get(int indice) {
        if (indice < 0 || indice >= tamanho) {
            throw new IndexOutOfBoundsException("Índice inválido: " + indice);
        }
        return dados[indice];
    }

    /** Busca sequencial pelo CPF. Retorna o índice no vetor ou -1 se não existir. */
    private int indiceDe(String cpf) {
        String chave = Contato.somenteDigitos(cpf);
        for (int i = 0; i < tamanho; i++) {
            if (Contato.somenteDigitos(dados[i].getCpf()).equals(chave)) {
                return i;
            }
        }
        return -1;
    }

    /** Retorna o contato com o CPF informado ou null se não estiver cadastrado. */
    public Contato buscar(String cpf) {
        int i = indiceDe(cpf);
        return i >= 0 ? dados[i] : null;
    }

    public boolean contem(String cpf) {
        return indiceDe(cpf) >= 0;
    }

    /**
     * Adiciona um contato ao final da lista.
     *
     * @return false se o CPF já estiver cadastrado (nada é gravado); true caso contrário.
     */
    public boolean adicionar(Contato contato) {
        if (contem(contato.getCpf())) {
            return false;
        }
        if (tamanho == dados.length) {
            aumentarCapacidade();
        }
        dados[tamanho++] = contato;
        return true;
    }

    /**
     * Exclui o contato com o CPF informado, deslocando os elementos seguintes
     * uma posição para a esquerda.
     *
     * @return true se excluiu; false se o CPF não existia (o chamador ignora em silêncio).
     */
    public boolean excluir(String cpf) {
        int i = indiceDe(cpf);
        if (i < 0) {
            return false;
        }
        for (int j = i; j < tamanho - 1; j++) {
            dados[j] = dados[j + 1];
        }
        dados[--tamanho] = null;
        return true;
    }

    /** Ordena a lista por nome (ignora maiúsculas/minúsculas e acentos) usando insertion sort. */
    public void ordenarPorNome() {
        Collator collator = Collator.getInstance(Locale.forLanguageTag("pt-BR"));
        collator.setStrength(Collator.PRIMARY);

        for (int i = 1; i < tamanho; i++) {
            Contato atual = dados[i];
            int j = i - 1;
            while (j >= 0 && collator.compare(dados[j].getNome(), atual.getNome()) > 0) {
                dados[j + 1] = dados[j];
                j--;
            }
            dados[j + 1] = atual;
        }
    }

    private void aumentarCapacidade() {
        Contato[] novo = new Contato[dados.length * 2];
        for (int i = 0; i < tamanho; i++) {
            novo[i] = dados[i];
        }
        dados = novo;
    }
}
