package repo;

import dbtools.DBCachePool;
import ents.User;
import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Witalia on 25.11.2014.
 */

/**
 * Class for operating with USERS table in database
 */
public class UserRepo {
    private static Logger logger = Logger.getLogger(UserRepo.class);

    /**
     * Get id of some user (byt his credentials)
     * @param pool database connection pool
     * @param user target user
     * @return id
     */
    public static int getId(DBCachePool pool, User user) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "select id from USERS where " +
                            "username = ? " +
                            "and passhash = ? " +
                            "and salt = ?"
            );
            statement.setString(1, user.getUsername());
            statement.setString(2, user.getPassHash());
            statement.setString(3, user.getSalt());
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt(1);
            }
            return -1;
        } catch (SQLException e) {
            logger.error("Connection failed", e);
            return -1;
        } finally {
            pool.putConnection(connection);
        }
    }

    /**
     * Get SALT associated with this user (by his name).
     * @param pool database connection pool
     * @param user target user.
     * @return SALT of this user.
     */
    public static String getSalt(DBCachePool pool, User user) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "select salt from USERS where " +
                            "username = ?"
            );
            statement.setString(1, user.getUsername());
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getString(1);
            }
            return null;
        } catch (SQLException e) {
            logger.error("Connection failed", e);
            return null;
        } finally {
            pool.putConnection(connection);
        }
    }

    /**
     * When it's possible (username is not taken),
     * add a new user to table (register).
     * @param pool database connection pool
     * @param user new user
     * @return true if successfully
     */
    public static boolean register(DBCachePool pool, User user) {
        if (checkExists(pool, user)) {
            return false;
        }
        Connection connection = null;
        user.setSalt();
        user.hashPass();
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "insert into USERS values (default, ?, ?, ?)"
            );
            statement.setString(1, user.getUsername());
            statement.setString(2, user.getPassHash());
            statement.setString(3, user.getSalt());
            statement.executeUpdate();
            return true;
        } catch (SQLException e) {
            logger.error("Can't register user", e);
            return false;
        } finally {
            pool.putConnection(connection);
        }
    }

    /**
     * Check if user entered correct credentials.
     * @param pool database connection pool
     * @param user
     * @return true if credentials are correct
     */
    public static boolean checkCredentials(DBCachePool pool, User user) {
        user.setSalt(getSalt(pool, user));
        user.hashPass();
        user.setId(getId(pool, user));
        return user.getId() != -1;
    }

    /**
     * Check if user's username is taken.
     * @param pool database connection pool.
     * @param user target user.
     * @return true if taken
     */
    public static boolean checkExists(DBCachePool pool, User user) {
        return getSalt(pool, user) != null;
    }

    /**
     * Get list of all records from database.
     * @param pool database connection pool
     * @return array of users
     */
    public static User[] getAll(DBCachePool pool) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "select * from USERS"
            );
            ResultSet resultSet = statement.executeQuery();
            List<User> userList = new ArrayList<>();
            while (resultSet.next()) {
                userList.add(getOne(resultSet));
            }
            return userList.toArray(new User[userList.size()]);
        } catch (SQLException e) {
            logger.error("Connection failed", e);
            return null;
        } finally {
            pool.putConnection(connection);
        }
    }

    /**
     * Find user record by his id.
     * @param pool database connection pool
     * @param id id of a user
     * @return user
     */
    public static User getByID(DBCachePool pool, int id) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "select * from USERS where id = ?"
            );
            statement.setInt(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return getOne(resultSet);
            }
            return null;
        } catch (SQLException e) {
            logger.error("Can't get user", e);
            return null;
        } finally {
            pool.putConnection(connection);
        }
    }

    /**
     * Get user from current record in ResultSet.
     * @param resultSet
     * @return user
     * @throws SQLException
     */
    private static User getOne(ResultSet resultSet) throws SQLException {
        User res = new User();
        res.setId(resultSet.getInt(1));
        res.setUsername(resultSet.getString(2));
        res.setPassHash(resultSet.getString(3));
        res.setSalt(resultSet.getString(4));
        return res;
    }
}
