package sample;

import javax.swing.table.AbstractTableModel;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.util.*;

/**
 * Created by Witalia on 01.12.2014.
 */
class DBTableModel extends AbstractTableModel {
    private Database database;
    private String tableName;
    private String[] columns;
    private java.util.List<Object[]> data;

    private Map<Object[], Object[]> original = new HashMap<>();
    private Set<Object[]> added = new HashSet<>();
    private Set<Object[]> removed = new HashSet<>();
    private Set<Object[]> modified = new HashSet<>();

    public DBTableModel(Database database, String tableName) {
        this.database = database;
        this.tableName = tableName;

        readFromDatabase();
        saveOriginals();
    }

    private void init() {
        original.clear();
        modified.clear();
        added.clear();
        removed.clear();
    }

    private void readFromDatabase() {
        ResultSet resultSet = database.getAll(tableName);
        columns = (String[])database.getColumnInfo(resultSet, ResultSetMetaData::getColumnName);
        data = database.getRows(resultSet);
    }

    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return columnIndex > 0;
    }

    @Override
    public String getColumnName(int column) {
        return columns[column];
    }

    @Override
    public int getRowCount() {
        return data.size();
    }

    @Override
    public int getColumnCount() {
        return columns.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        return data.get(rowIndex)[columnIndex];
    }

    private void saveOriginals() {
        for (Object[] row : data) {
            original.put(row, row.clone());
        }
    }

    public void addRow() {
        Object[] newRow = new Object[columns.length];
        Object[] origin = newRow.clone();
        data.add(newRow);
        added.add(origin);
        original.put(newRow, origin);
        fireTableRowsInserted(data.size() - 1, data.size());
    }

    public void deleteRows(int[] selected) {
        if (selected == null || selected.length == 0) {
            return;
        }
        Arrays.sort(selected);
        for (int i = selected.length - 1; i >= 0; i--) {
            removed.add(original.get(data.get(selected[i])));
            data.remove(selected[i]);
        }
        fireTableRowsDeleted(selected[0], selected[selected.length - 1]);
    }

    public void commit() {
        for (Object[] row : removed) {
            if (added.contains(row) == false) {
                database.removeRow(tableName, columns, row);
            }
        }

        for (Object[] row : modified) {
            Object[] origin = original.get(row);
            if (removed.contains(origin) == false) {
                if (added.contains(origin) == true) {
                    database.addRow(tableName, columns.length, row);
                } else {
                    database.updateRow(tableName, columns, origin, row);
                }
            }
        }

        init();
        saveOriginals();
    }

    @Override
    public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
        data.get(rowIndex)[columnIndex] = aValue;
        modified.add(data.get(rowIndex));
        fireTableCellUpdated(rowIndex, columnIndex);
    }
}