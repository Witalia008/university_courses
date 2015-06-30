import java.sql.*;

/**
 * Created by Witalia on 26.10.2014.
 */
public class Database {
    private Connection connection = null;
    private PreparedStatement preparedStatement = null;

    public Database() {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost/reports",
                    "Witalia",
                    "password"
            );

            preparedStatement = connection.prepareStatement(
                    "insert into file_read_reports values (default, ?, ?, ?)"
            );
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Connection getConnection() {
        return connection;
    }

    public void insert(String fileName, boolean success, String errorName) {
        try {
            preparedStatement.setString(1, fileName);
            preparedStatement.setBoolean(2, success);
            preparedStatement.setString(3, errorName);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
