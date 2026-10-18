package model;

public class Carro extends Veiculo {
    private static final double TAXA_PROTECAO = 0.10;

    private final int portas;

    public Carro(String placa, String modelo, double valorDiaria, int portas) {
        super(placa, modelo, valorDiaria);
        this.portas = portas;
    }

    public int getPortas() {
        return portas;
    }

    @Override
    public double calcularLocacao(int diarias) {
        double subtotal = diarias * getValorDiaria();
        return subtotal + subtotal * TAXA_PROTECAO;
    }

    @Override
    protected String getCaracteristica() {
        return "Portas: " + portas;
    }
}