package sample;

import javax.swing.*;
import java.awt.*;
import java.sql.SQLException;

/**
 * Created by Witalia on 01.12.2014.
 */
public class Main extends JFrame {
    public Main() throws HeadlessException {
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(700, 500));

        DBTablePanel tablePanel = new DBTablePanel();
        add(tablePanel, BorderLayout.CENTER);

        pack();
        setVisible(true);

        tablePanel.setDriverName("oracle.jdbc.driver.OracleDriver");
        tablePanel.setServiceURI("jdbc:oracle:thin:@localhost:1521:xe");
        tablePanel.setUsername("Witalia");
        tablePanel.setPassword("password");
        tablePanel.setTableName("USERS");
        tablePanel.showTable();
    }

    public static void main(String[] args) throws SQLException {
        SwingUtilities.invokeLater(() -> new Main());
    }
}
