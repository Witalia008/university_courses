package sample;

import javax.swing.*;
import java.awt.*;
import java.sql.SQLException;

/**
 * Created by Witalia on 01.12.2014.
 */
public class DBTablePanel extends JPanel {
    private String driverName;
    private String serviceURI;
    private String username;
    private String password;
    private String tableName;
    private JTable table;
    private JScrollPane pane;
    private DBTableModel model;

    public DBTablePanel() {
        setLayout(new BorderLayout());

        JPanel buttonPanel = new JPanel();
        JButton buttonAdd = new JButton("Add row");
        JButton buttonRemove = new JButton("Remove rows");
        JButton buttonCommit = new JButton("Commit");

        buttonPanel.add(buttonAdd);
        buttonPanel.add(buttonRemove);
        buttonPanel.add(buttonCommit);
        add(buttonPanel, BorderLayout.SOUTH);

        buttonAdd.addActionListener(e -> model.addRow());
        buttonRemove.addActionListener(e -> model.deleteRows(table.getSelectedRows()));
        buttonCommit.addActionListener(e -> model.commit());
    }

    public boolean showTable() {
        if (username == null || password == null || tableName == null) {
            return false;
        }
        if (pane != null) {
            remove(pane);
        }
        getTable();
        pane = new JScrollPane(table);
        add(pane, BorderLayout.CENTER);
        return true;
    }

    private void getTable() {
        Database database;
        try {
            database = new Database(driverName, serviceURI, username, password);
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }
        model = new DBTableModel(database, tableName);
        table = new JTable(model);
        table.setFillsViewportHeight(true);
        table.getTableHeader().setReorderingAllowed(false);
    }

    public void setDriverName(String driverName) {
        this.driverName = driverName;
    }

    public void setServiceURI(String serviceURI) {
        this.serviceURI = serviceURI;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setTableName(String tableName) {
        this.tableName = tableName;
    }
}