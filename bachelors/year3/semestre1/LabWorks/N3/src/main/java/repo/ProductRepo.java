package repo;

import dbtools.DBCachePool;
import ents.Product;
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
 * Class for operating with PRODUCTS table in database
 */
public class ProductRepo {
    private static Logger logger = Logger.getLogger(ProductRepo.class);

    /**
     * Get all records from table
     * @param pool database connection pool
     * @return array of products
     */
    public static Product[] getAllProducts(DBCachePool pool) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "select * from PRODUCTS"
            );
            ResultSet resultSet = statement.executeQuery();
            List<Product> productList = new ArrayList<>();
            while (resultSet.next()) {
                productList.add(getOne(resultSet));
            }
            return productList.toArray(new Product[productList.size()]);
        } catch (SQLException e) {
            logger.error("Connection failed", e);
            return null;
        } finally {
            pool.putConnection(connection);
        }
    }

    /**
     * Add a new record to table or modify old one.
     * @param pool database connection pool
     * @param product item to add
     * @return true if successfully added
     */
    public static boolean add(DBCachePool pool, Product product) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "delete from PRODUCTS where id = ?"
            );
            statement.setInt(1, product.getId());
            statement.executeUpdate();
            statement = connection.prepareStatement(
                    "insert into PRODUCTS values (default, ?, ?, ?, ?)"
            );
            statement.setString(1, product.getType());
            statement.setString(2, product.getName());
            statement.setInt(3, product.getPrice());
            statement.setString(4, product.getDescription());
            statement.executeUpdate();
            return true;
        } catch (SQLException e) {
            logger.error("Can't add product", e);
            return false;
        } finally {
            pool.putConnection(connection);
        }
    }

    /**
     * Get record from table by it's id.
     * @param pool database connection pool
     * @param id id of wanted item
     * @return desired product or null in case of failure
     */
    public static Product getByID(DBCachePool pool, int id) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "select * from PRODUCTS where id = ?"
            );
            statement.setInt(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return getOne(resultSet);
            }
        } catch (SQLException e) {
            logger.error("Can't get product", e);
        } finally {
            pool.putConnection(connection);
        }
        return null;
    }

    /**
     * Get current record from ResultSet as Product
     * @param resultSet
     * @return
     * @throws SQLException
     */
    private static Product getOne(ResultSet resultSet) throws SQLException {
        Product cur = new Product();
        cur.setId(resultSet.getInt(1));
        cur.setType(resultSet.getString(2));
        cur.setName(resultSet.getString(3));
        cur.setPrice(resultSet.getInt(4));
        cur.setDescription(resultSet.getString(5));
        return cur;
    }
}
