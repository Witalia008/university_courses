package Sample.utils;

import javax.xml.crypto.Data;
import java.sql.*;

/**
 * Created by Witalia on 17.11.2014.
 */
public class Database {
    protected Connection connection;

    static {
        try {
            Class.forName("oracle.jdbc.driver.OracleDriver");
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
    }

    public static Database getDatabase(String username, String password) {
        Database res = new Database();
        try {
            res.connection = DriverManager.getConnection(
                    "jdbc:oracle:thin:@localhost:1521:xe",
                    username, password);
        } catch (SQLException e) {
            e.printStackTrace();
            res = null;
        }
        return res;
    }

    public boolean addUser(User user) {
        if (getProperty("username", user) != null) {
            return false;
        }
        user.setSalt();
        user.hashPass();
        try {
            PreparedStatement statement = connection.prepareStatement(
                    "insert into users values (default, ?, ?, ?)"
            );
            statement.setString(1, user.getUsername());
            statement.setString(2, user.getPassHash());
            statement.setString(3, user.getSalt());
            statement.executeUpdate();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public String getProperty(String property, User user) {
        try {
            String query = "select * from users where username = ?"
                    + (user.getPassHash() != null ? " and passhash = ?" : "");
            PreparedStatement statement =
                    connection.prepareStatement(query);
            statement.setString(1, user.getUsername());
            if (user.getPassHash() != null) {
                statement.setString(2, user.getPassHash());
            }
            ResultSet res = statement.executeQuery();
            if (!res.next()) {
                return null;
            }
            return res.getString(property);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public boolean checkCredentials(User user) {
        String salt = getProperty("salt", user);
        if (salt == null) {
            return false;
        }
        user.setSalt(salt);
        user.hashPass();
        return getProperty("username", user) != null;
    }
}
