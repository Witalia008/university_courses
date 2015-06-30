package dbtools;

/**
 * Created by Witalia on 22.11.2014.
 */
import javafx.util.Pair;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Witalia on 26.10.2014.
 */
public class Database {
    private static Connection connection = null;
    private static PreparedStatement preparedStatement = null;

    static {
        setupConnection();
    }
    public static void setupConnection() {
        if (connection != null) {
            return;
        }
        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost/points",
                    "Witalia",
                    "password"
            );

            preparedStatement = connection.prepareStatement(
                    "select px, py from points"
            );
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection() {
        return connection;
    }

    public static Pair get() {
        List<Integer> x = new ArrayList<>();
        List<Integer> y = new ArrayList<>();
        try {
            ResultSet res = preparedStatement.executeQuery();
            while (res.next()) {
                x.add(res.getInt(1));
                y.add(res.getInt(2));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return new Pair<>(x, y);
    }
}

