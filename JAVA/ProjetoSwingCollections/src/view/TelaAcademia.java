package view;

import exceptions.MatriculaBloqueadaException;
import interfaces.Avaliavel;
import model.AlunoAcademia;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class TelaAcademia extends JFrame {

    // Persistência 100% em memória
    private final List<AlunoAcademia> alunos = new ArrayList<>();

    private final JTextField txtMatricula = new JTextField(10);
    private final JTextField txtNome = new JTextField(20);
    private final JTextField txtPeso = new JTextField(10);
    private final JTextField txtAltura = new JTextField(10);
    private final JTextField txtMensalidade = new JTextField(10);

    private final JComboBox<String> cmbOperacao = new JComboBox<>(new String[]{
            "Registrar frequência", "Suspender por pendência", "Reativar matrícula"});
    private final JComboBox<String> cmbOrdem = new JComboBox<>(new String[]{
            "Por matrícula", "Por mensalidade"});

    private final JButton btnCadastrar = new JButton("Cadastrar");
    private final JButton btnPesquisar = new JButton("Pesquisar");
    private final JButton btnProcessar = new JButton("Processar Operação");
    private final JButton btnOrdenar = new JButton("Ordenar");
    private final JButton btnSair = new JButton("Sair");

    private final JTextArea txtRelatorio = new JTextArea(14, 60);

    public TelaAcademia() {
        super("Academia - Cadastro e Fichas de Treino");
        montarTela();
        registrarEventos();
        pack();
        setLocationRelativeTo(null);
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    }

    private void montarTela() {
        setLayout(new BorderLayout(8, 8));

        JPanel form = new JPanel(new GridLayout(5, 2, 5, 5));
        form.setBorder(BorderFactory.createTitledBorder("Dados do aluno"));
        form.add(new JLabel("Matrícula:"));        form.add(txtMatricula);
        form.add(new JLabel("Nome:"));             form.add(txtNome);
        form.add(new JLabel("Peso (kg):"));        form.add(txtPeso);
        form.add(new JLabel("Altura (m):"));       form.add(txtAltura);
        form.add(new JLabel("Mensalidade (R$):")); form.add(txtMensalidade);

        JPanel botoes = new JPanel(new FlowLayout(FlowLayout.CENTER, 8, 8));
        botoes.add(btnCadastrar);
        botoes.add(btnPesquisar);
        botoes.add(cmbOperacao);
        botoes.add(btnProcessar);
        botoes.add(cmbOrdem);
        botoes.add(btnOrdenar);
        botoes.add(btnSair);

        JPanel topo = new JPanel(new BorderLayout());
        topo.add(form, BorderLayout.NORTH);
        topo.add(botoes, BorderLayout.CENTER);

        txtRelatorio.setEditable(false);
        txtRelatorio.setFont(new Font(Font.MONOSPACED, Font.PLAIN, 12));

        add(topo, BorderLayout.NORTH);
        add(new JScrollPane(txtRelatorio), BorderLayout.CENTER);
    }

    private void registrarEventos() {
        btnCadastrar.addActionListener(e -> cadastrar());
        btnPesquisar.addActionListener(e -> pesquisar());
        btnProcessar.addActionListener(e -> processarOperacao());
        btnOrdenar.addActionListener(e -> ordenar());
        btnSair.addActionListener(e -> sair());

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                sair();
            }
        });
    }

    // ---------- Ações ----------

    private void cadastrar() {
        try {
            int matricula = Integer.parseInt(txtMatricula.getText().trim());
            String nome = txtNome.getText().trim();
            double peso = Double.parseDouble(txtPeso.getText().trim().replace(',', '.'));
            double altura = Double.parseDouble(txtAltura.getText().trim().replace(',', '.'));
            double mensalidade = Double.parseDouble(txtMensalidade.getText().trim().replace(',', '.'));

            if (nome.isEmpty()) {
                aviso("Informe o nome do aluno.");
                return;
            }
            if (!Avaliavel.medidasValidas(peso, altura)) {
                aviso("Peso ou altura fora de uma faixa válida (altura em metros, ex.: 1,75).");
                return;
            }
            AlunoAcademia novo = new AlunoAcademia(matricula, nome, peso, altura, mensalidade);
            if (alunos.contains(novo)) { // usa equals()
                aviso("Já existe aluno com a matrícula " + matricula + ".");
                return;
            }
            alunos.add(novo);
            limparCampos();
            listarAtivos("Aluno cadastrado com sucesso!");
        } catch (NumberFormatException ex) {
            erro("Preencha matrícula (inteiro), peso, altura e mensalidade com números válidos.");
        }
    }

    private void pesquisar() {
        AlunoAcademia a = buscarPelaMatriculaDigitada();
        if (a != null) {
            txtRelatorio.setText("=== RESULTADO DA PESQUISA ===\n" + a + "\n");
            txtNome.setText(a.getNome());
            txtPeso.setText(String.valueOf(a.getPeso()));
            txtAltura.setText(String.valueOf(a.getAltura()));
            txtMensalidade.setText(String.valueOf(a.getMensalidade()));
        }
    }

    private void processarOperacao() {
        AlunoAcademia a = buscarPelaMatriculaDigitada();
        if (a == null) return;

        try {
            switch (cmbOperacao.getSelectedIndex()) {
                case 0:
                    a.registrarFrequencia(); // pode lançar MatriculaBloqueadaException
                    sucesso("Frequência registrada para " + a.getNome() + ".");
                    break;
                case 1:
                    a.suspender();
                    sucesso("Matrícula de " + a.getNome() + " suspensa por pendência.");
                    break;
                case 2:
                    a.reativar();
                    sucesso("Matrícula de " + a.getNome() + " reativada.");
                    break;
                default:
                    break;
            }
            listarAtivos("Operação concluída.");
        } catch (MatriculaBloqueadaException ex) {
            JOptionPane.showMessageDialog(this, ex.getMessage(),
                    "Matrícula bloqueada", JOptionPane.WARNING_MESSAGE);
        }
    }

    private void ordenar() {
        if (alunos.isEmpty()) {
            aviso("Não há alunos cadastrados.");
            return;
        }
        if (cmbOrdem.getSelectedIndex() == 0) {
            Collections.sort(alunos); // Comparable (matrícula)
        } else {
            Collections.sort(alunos, AlunoAcademia.POR_MENSALIDADE);
        }
        listarAtivos("Lista ordenada (" + cmbOrdem.getSelectedItem() + ")");
    }

    private void listarAtivos(String titulo) {
        StringBuilder sb = new StringBuilder("=== " + titulo + " ===\n");
        int ativos = 0;
        for (AlunoAcademia a : alunos) {
            if (!a.isSuspenso()) {
                sb.append(a).append("\n");
                ativos++;
            }
        }
        sb.append("\nAlunos ativos: ").append(ativos)
          .append(" | Suspensos: ").append(alunos.size() - ativos).append("\n");
        txtRelatorio.setText(sb.toString());
    }

    private void sair() {
        int r = JOptionPane.showConfirmDialog(this, "Deseja realmente sair?",
                "Sair", JOptionPane.YES_NO_OPTION);
        if (r == JOptionPane.YES_OPTION) {
            dispose();
            System.exit(0);
        }
    }

    // ---------- Auxiliares ----------

    private AlunoAcademia buscarPelaMatriculaDigitada() {
        try {
            int matricula = Integer.parseInt(txtMatricula.getText().trim());
            for (AlunoAcademia a : alunos) {
                if (a.getMatricula() == matricula) return a;
            }
            aviso("Matrícula " + matricula + " não encontrada.");
        } catch (NumberFormatException ex) {
            erro("Informe uma matrícula numérica válida.");
        }
        return null;
    }

    private void limparCampos() {
        txtMatricula.setText("");
        txtNome.setText("");
        txtPeso.setText("");
        txtAltura.setText("");
        txtMensalidade.setText("");
        txtMatricula.requestFocus();
    }

    private void aviso(String msg) {
        JOptionPane.showMessageDialog(this, msg, "Atenção", JOptionPane.WARNING_MESSAGE);
    }

    private void erro(String msg) {
        JOptionPane.showMessageDialog(this, msg, "Erro", JOptionPane.ERROR_MESSAGE);
    }

    private void sucesso(String msg) {
        JOptionPane.showMessageDialog(this, msg, "Sucesso", JOptionPane.INFORMATION_MESSAGE);
    }
}
