package controller;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.NoSuchElementException;
import java.util.Scanner;

import model.Carro;
import model.Motocicleta;
import model.Veiculo;

public class App {
    private static final Locale BR = Locale.forLanguageTag("pt-BR");
    private static final Scanner scanner = new Scanner(System.in);
    private static final List<Veiculo> veiculos = new ArrayList<>();
    private static double totalArrecadado = 0;

    public static void main(String[] args) {
        int opcao = 0;
        try {
            do {
                exibirMenu();
                opcao = lerInt("Escolha uma opção: ");
                switch (opcao) {
                    case 1 -> cadastrarVeiculo();
                    case 2 -> listarVeiculos();
                    case 3 -> alugarVeiculo();
                    case 4 -> devolverVeiculo();
                    case 5 -> consultarVeiculo();
                    case 6 -> System.out.println("Total arrecadado: " + moeda(totalArrecadado));
                    case 9 -> System.out.println("Programa encerrado.");
                    default -> System.out.println("Opção inválida.");
                }
            } while (opcao != 9);
        } catch (NoSuchElementException e) {
            System.out.println("\nEntrada encerrada. Programa finalizado.");
        }
    }

    private static void exibirMenu() {
        System.out.println("\n===== LOCADORA DE VEÍCULOS =====");
        System.out.println("1. Cadastrar veículo");
        System.out.println("2. Listar veículos");
        System.out.println("3. Alugar veículo");
        System.out.println("4. Devolver veículo");
        System.out.println("5. Consultar veículo pela placa");
        System.out.println("6. Exibir total arrecadado");
        System.out.println("9. Encerrar o programa");
    }

    private static void cadastrarVeiculo() {
        int tipo;
        do {
            tipo = lerInt("Tipo (1 - Carro, 2 - Motocicleta): ");
        } while (tipo != 1 && tipo != 2);

        String placa;
        while (true) {
            placa = lerTexto("Placa: ").toUpperCase();
            if (placa.isEmpty()) {
                System.out.println("A placa não pode ser vazia.");
            } else if (buscarPorPlaca(placa) != null) {
                System.out.println("Já existe um veículo cadastrado com essa placa.");
            } else {
                break;
            }
        }

        String modelo = lerTexto("Modelo: ");
        while (modelo.isEmpty()) {
            System.out.println("O modelo não pode ser vazio.");
            modelo = lerTexto("Modelo: ");
        }

        double diaria = lerDoublePositivo("Valor da diária (R$): ");

        if (tipo == 1) {
            int portas = lerIntPositivo("Quantidade de portas: ");
            veiculos.add(new Carro(placa, modelo, diaria, portas));
        } else {
            int cilindrada = lerIntPositivo("Cilindrada (cc): ");
            veiculos.add(new Motocicleta(placa, modelo, diaria, cilindrada));
        }
        System.out.println("Veículo cadastrado com sucesso.");
    }

    private static void listarVeiculos() {
        if (veiculos.isEmpty()) {
            System.out.println("Nenhum veículo cadastrado.");
            return;
        }
        for (Veiculo v : veiculos) {
            System.out.println(v.exibirDados());
        }
    }

    private static void alugarVeiculo() {
        Veiculo v = buscarPorPlaca(lerTexto("Placa do veículo: "));
        if (v == null) {
            System.out.println("Placa não cadastrada.");
            return;
        }
        if (v.isAlugado()) {
            System.out.println("Este veículo já está alugado.");
            return;
        }
        int diarias = lerInt("Quantidade de diárias: ");
        if (v.alugar(diarias)) {
            double valor = v.calcularLocacao(diarias);
            totalArrecadado += valor;
            System.out.println("Locação realizada. Valor: " + moeda(valor));
        } else {
            System.out.println("Não foi possível alugar: a quantidade de diárias deve ser maior que zero.");
        }
    }

    private static void devolverVeiculo() {
        Veiculo v = buscarPorPlaca(lerTexto("Placa do veículo: "));
        if (v == null) {
            System.out.println("Placa não cadastrada.");
        } else if (v.devolver()) {
            System.out.println("Veículo devolvido. Situação: " + v.getSituacao());
        } else {
            System.out.println("Este veículo não está alugado.");
        }
    }

    private static void consultarVeiculo() {
        Veiculo v = buscarPorPlaca(lerTexto("Placa do veículo: "));
        System.out.println(v == null ? "Placa não cadastrada." : v.exibirDados());
    }

    private static Veiculo buscarPorPlaca(String placa) {
        for (Veiculo v : veiculos) {
            if (v.getPlaca().equalsIgnoreCase(placa.trim())) {
                return v;
            }
        }
        return null;
    }

    private static String moeda(double valor) {
        return String.format(BR, "R$ %.2f", valor);
    }

    private static String lerTexto(String mensagem) {
        System.out.print(mensagem);
        return scanner.nextLine().trim();
    }

    private static int lerInt(String mensagem) {
        while (true) {
            try {
                return Integer.parseInt(lerTexto(mensagem));
            } catch (NumberFormatException e) {
                System.out.println("Entrada inválida. Digite um número inteiro.");
            }
        }
    }

    private static int lerIntPositivo(String mensagem) {
        while (true) {
            int n = lerInt(mensagem);
            if (n > 0) {
                return n;
            }
            System.out.println("O valor deve ser maior que zero.");
        }
    }

    private static double lerDoublePositivo(String mensagem) {
        while (true) {
            try {
                double n = Double.parseDouble(lerTexto(mensagem).replace(',', '.'));
                if (n > 0) {
                    return n;
                }
                System.out.println("O valor deve ser maior que zero.");
            } catch (NumberFormatException e) {
                System.out.println("Entrada inválida. Digite um número (ex.: 100,00).");
            }
        }
    }
}