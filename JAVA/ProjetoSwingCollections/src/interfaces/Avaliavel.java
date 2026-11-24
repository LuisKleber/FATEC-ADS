package interfaces;

/**
 * Contrato de avaliação física. Garante comportamento polimórfico
 * para qualquer classe do domínio que possa ser avaliada.
 */
public interface Avaliavel {

    double getPeso();

    double getAltura();

    /** IMC = peso / (altura * altura). */
    double calcularIndiceMassaCorporal();

    /** Método default: classificação baseada no IMC calculado. */
    default String classificarIMC() {
        double imc = calcularIndiceMassaCorporal();
        if (imc < 18.5) return "Abaixo do peso";
        if (imc < 25.0) return "Peso normal";
        if (imc < 30.0) return "Sobrepeso";
        return "Obesidade";
    }

    /** Método static: validação de medidas corporais. */
    static boolean medidasValidas(double peso, double altura) {
        return peso > 0 && peso < 400 && altura > 0.5 && altura < 2.5;
    }
}
