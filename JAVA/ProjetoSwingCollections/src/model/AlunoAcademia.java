package model;

import exceptions.MatriculaBloqueadaException;
import interfaces.Avaliavel;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;

public class AlunoAcademia implements Comparable<AlunoAcademia>, Avaliavel {

    /** Ordenação alternativa: por mensalidade. */
    public static final Comparator<AlunoAcademia> POR_MENSALIDADE =
            Comparator.comparingDouble(AlunoAcademia::getMensalidade);

    private int matricula;
    private String nome;
    private double peso;
    private double altura;
    private double mensalidade;
    private boolean suspenso;
    private final List<LocalDate> frequencias = new ArrayList<>();

    public AlunoAcademia(int matricula, String nome, double peso, double altura, double mensalidade) {
        this.matricula = matricula;
        this.nome = nome;
        this.peso = peso;
        this.altura = altura;
        this.mensalidade = mensalidade;
    }

    // ---------- Regras de negócio ----------

    public void registrarFrequencia() throws MatriculaBloqueadaException {
        if (suspenso) {
            throw new MatriculaBloqueadaException(matricula,
                    "Matrícula " + matricula + " suspensa por pendência. Regularize para treinar.");
        }
        frequencias.add(LocalDate.now());
    }

    public void suspender() {
        this.suspenso = true;
    }

    public void reativar() {
        this.suspenso = false;
    }

    @Override
    public double calcularIndiceMassaCorporal() {
        return peso / (altura * altura);
    }

    // ---------- Getters / Setters ----------

    public int getMatricula() { return matricula; }
    public void setMatricula(int matricula) { this.matricula = matricula; }

    public String getNome() { return nome; }
    public void setNome(String nome) { this.nome = nome; }

    @Override
    public double getPeso() { return peso; }
    public void setPeso(double peso) { this.peso = peso; }

    @Override
    public double getAltura() { return altura; }
    public void setAltura(double altura) { this.altura = altura; }

    public double getMensalidade() { return mensalidade; }
    public void setMensalidade(double mensalidade) { this.mensalidade = mensalidade; }

    public boolean isSuspenso() { return suspenso; }

    public List<LocalDate> getFrequencias() { return frequencias; }

    // ---------- Comparable / equals / hashCode / toString ----------

    @Override
    public int compareTo(AlunoAcademia outro) {
        return Integer.compare(this.matricula, outro.matricula);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof AlunoAcademia)) return false;
        AlunoAcademia that = (AlunoAcademia) o;
        return matricula == that.matricula;
    }

    @Override
    public int hashCode() {
        return Objects.hash(matricula);
    }

    @Override
    public String toString() {
        return String.format("Matrícula: %d | %s | Peso: %.1f kg | Altura: %.2f m | IMC: %.1f (%s) | "
                        + "Mensalidade: R$ %.2f | Frequências: %d | Status: %s",
                matricula, nome, peso, altura, calcularIndiceMassaCorporal(), classificarIMC(),
                mensalidade, frequencias.size(), suspenso ? "SUSPENSO" : "ATIVO");
    }
}
