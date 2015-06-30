package repo;

import dbtools.DBCachePool;
import ents.Order;
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
 * Class for getting from or updating in ORDERS tables in database
 */
public class OrderRepo {
    private static Logger logger = Logger.getLogger(OrderRepo.class);

    /**
     * Get all records in table
     * @param pool
     * @return
     */
    public static Order[] getAll(DBCachePool pool) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "select * from ORDERS"
            );
            ResultSet resultSet = statement.executeQuery();
            List<Order> result = new ArrayList<>();
            while (resultSet.next()) {
                Order cur = new Order();
                cur.setId(resultSet.getInt(1));
                cur.setProductId(resultSet.getInt(2));
                cur.setUserId(resultSet.getInt(3));
                cur.setAmount(resultSet.getInt(4));
                cur.setTotal(resultSet.getInt(5));
                result.add(cur);
            }
            return result.toArray(new Order[result.size()]);
        } catch (SQLException e) {
            logger.error("Can't get all orders", e);
            return null;
        } finally {
            pool.putConnection(connection);
        }
    }

    public static Order[] getByUserId(DBCachePool pool, User user) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "select * from ORDERS where user_id = ?"
            );
            statement.setInt(1, user.getId());
            ResultSet resultSet = statement.executeQuery();
            List<Order> result = new ArrayList<>();
            while (resultSet.next()) {
                Order cur = new Order();
                cur.setId(resultSet.getInt(1));
                cur.setProductId(resultSet.getInt(2));
                cur.setUserId(resultSet.getInt(3));
                cur.setAmount(resultSet.getInt(4));
                cur.setTotal(resultSet.getInt(5));
                result.add(cur);
            }
            return result.toArray(new Order[result.size()]);
        } catch (SQLException e) {
            logger.error("Can't get all orders", e);
            return null;
        } finally {
            pool.putConnection(connection);
        }
    }

    /**
     * Deletes orders of current user from database.
     * @param pool database connection pool
     * @param user
     */
    public static void deleteByUserId(DBCachePool pool, User user) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "delete from ORDERS where user_id = ?"
            );
            statement.setInt(1, user.getId());
            statement.executeUpdate();
        } catch (SQLException e) {
            logger.error("Can't delete user's orders", e);
        } finally {
            pool.putConnection(connection);
        }
    }

    /**
     * Add a new record into table
     * @param pool
     * @param order record to add
     * @return
     */
    public static boolean add(DBCachePool pool, Order order) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "insert into ORDERS values (default, ?, ?, ?, ?)"
            );
            statement.setInt(1, order.getProductId());
            statement.setInt(2, order.getUserId());
            statement.setInt(3, order.getAmount());
            statement.setInt(4, order.getTotal());
            statement.executeUpdate();
            return true;
        } catch (SQLException e) {
            logger.error("Can't add order", e);
            return false;
        } finally {
            pool.putConnection(connection);
        }
    }
}
