import view.TelaAcademia;

public class Main {
    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(() -> {
            TelaAcademia tela = new TelaAcademia();
            tela.setVisible(true);
        });
    }
}
