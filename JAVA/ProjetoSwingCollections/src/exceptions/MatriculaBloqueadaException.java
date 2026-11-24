package exceptions;

/**
 * Checked Exception: lançada quando se tenta uma operação
 * (ex.: registrar frequência) em uma matrícula suspensa por pendência.
 */
public class MatriculaBloqueadaException extends Exception {

    private final int matricula;

    public MatriculaBloqueadaException(int matricula, String mensagem) {
        super(mensagem);
        this.matricula = matricula;
    }

    public int getMatricula() {
        return matricula;
    }
}
