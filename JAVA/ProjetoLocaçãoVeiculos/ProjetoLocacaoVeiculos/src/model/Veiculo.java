package model;

import java.util.Locale;

public abstract class Veiculo {
    private final String placa;
    private final String modelo;
    private final double valorDiaria;
    private boolean alugado;

    public Veiculo(String placa, String modelo, double valorDiaria) {
        this.placa = placa;
        this.modelo = modelo;
        this.valorDiaria = valorDiaria;
        this.alugado = false;
    }

    public String getPlaca() {
        return placa;
    }

    public String getModelo() {
        return modelo;
    }

    public double getValorDiaria() {
        return valorDiaria;
    }

    public boolean isAlugado() {
        return alugado;
    }

    public String getSituacao() {
        return alugado ? "Alugado" : "Disponível";
    }

    /** Aluga o veículo se ele estiver disponível e as diárias forem maiores que zero. */
    public boolean alugar(int diarias) {
        if (alugado || diarias <= 0) {
            return false;
        }
        alugado = true;
        return true;
    }

    /** Devolve o veículo. Retorna false se ele já estava disponível. */
    public boolean devolver() {
        if (!alugado) {
            return false;
        }
        alugado = false;
        return true;
    }

    /** Cada tipo de veículo aplica sua própria regra de cálculo. */
    public abstract double calcularLocacao(int diarias);

    /** Característica específica de cada tipo (portas, cilindrada...). */
    protected abstract String getCaracteristica();

    public String exibirDados() {
        return String.format(Locale.forLanguageTag("pt-BR"),
                "%s | Placa: %s | Modelo: %s | Diária: R$ %.2f | %s | Situação: %s",
                getClass().getSimpleName(), placa, modelo, valorDiaria,
                getCaracteristica(), getSituacao());
    }
}