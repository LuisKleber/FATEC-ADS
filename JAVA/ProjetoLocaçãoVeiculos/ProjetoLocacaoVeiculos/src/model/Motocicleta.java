package model;

public class Motocicleta extends Veiculo {
    private static final double TAXA_EQUIPAMENTOS = 25.00;

    private final int cilindrada;

    public Motocicleta(String placa, String modelo, double valorDiaria, int cilindrada) {
        super(placa, modelo, valorDiaria);
        this.cilindrada = cilindrada;
    }

    public int getCilindrada() {
        return cilindrada;
    }

    @Override
    public double calcularLocacao(int diarias) {
        return diarias * getValorDiaria() + TAXA_EQUIPAMENTOS;
    }

    @Override
    protected String getCaracteristica() {
        return "Cilindrada: " + cilindrada + "cc";
    }
}