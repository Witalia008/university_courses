package sample;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Witalia on 01.12.2014.
 */
public class Database {
    private Connection connection;

    public Database(String driverName, String uri, String username, String password) throws SQLException {
        try {
            Class.forName(driverName);
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
        connection = DriverManager.getConnection(uri,
                username, password);
    }

    public ResultSet getAll(String tableName) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "select * from " + tableName
            );
            return statement.executeQuery();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public void insert(String tableName, List<String> list) {
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "insert into " + tableName + " values ("
                            + String.join(", ", list) + ")"
            );
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    interface ColumnCall {
        Object get(ResultSetMetaData r, int i) throws SQLException;
    }
    public Object[] getColumnInfo(ResultSet resultSet, ColumnCall caller) {
        try {
            ResultSetMetaData resultSetMetaData = resultSet.getMetaData();
            Object[] res = new String[resultSetMetaData.getColumnCount()];
            for (int i = 0; i < res.length; i++) {
                res[i] = caller.get(resultSetMetaData, i + 1);
            }
            return res;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public List<Object[]> getRows(ResultSet resultSet) {
        if (resultSet == null) {
            return new ArrayList<>();
        }
        List<Object[]> rows = new ArrayList<>();
        try {
            while (resultSet.next()) {
                Object[] cur = new Object[resultSet.getMetaData().getColumnCount()];
                for (int i = 0; i < cur.length; i++) {
                    cur[i] = resultSet.getObject(i + 1);
                }
                rows.add(cur);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return rows;
    }

    public void removeRow(String tableName, String[] columns, Object[] row) {
        StringBuffer sql = new StringBuffer("delete from " + tableName + " where");
        for (int i = 0; i < columns.length; i++) {
            sql.append((i == 0 ? " " : " and ") + columns[i] + " = "
                    + getStringRepr(i < row.length ? row[i] : null));
        }
        updateStatement(sql.toString());
    }

    public void addRow(String tableName, int columnsN, Object[] row) {
        StringBuffer sql = new StringBuffer("insert into " + tableName + " values ");
        for (int i = 0; i < columnsN; i++) {
            sql.append((i == 0 ? "(" : ", ")
                    + getStringRepr(i < row.length ? row[i] : null));
        }
        sql.append(")");
        updateStatement(sql.toString());
    }

    public void updateRow(String tableName, String[] columns, Object[] oldRow, Object[] newRow) {
        StringBuffer sql = new StringBuffer("update " + tableName + " set");
        for (int i = 0; i < columns.length; i++) {
            sql.append((i == 0 ? " " : ", ") +
                    columns[i] + " = " + getStringRepr(i < newRow.length ? newRow[i] : null));
        }
        sql.append(" where");
        for (int i = 0; i < columns.length; i++) {
            sql.append((i == 0 ? " " : " and ") + columns[i] + " = "
                    + getStringRepr(i < oldRow.length ? oldRow[i] : null));
        }
        updateStatement(sql.toString());
    }

    private String getStringRepr(Object obj) {
        if (obj == null) {
            return "default";
        }
        if (obj instanceof String) {
            return "'" + obj.toString() + "'";
        }
        return obj.toString();
    }

    private void updateStatement(String sql) {
        System.out.println(sql);
        try {
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
