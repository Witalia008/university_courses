package repo;

import dbtools.DBCachePool;
import ents.Role;
import ents.User;
import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * Created by Witalia on 25.11.2014.
 */

/**
 * Class for operating with ROLES tables in database
 */
public class RoleRepo {
    private static Logger logger = Logger.getLogger(RoleRepo.class);

    /**
     * Get role of specific user
     * @param pool database connection pool
     * @param user target user
     * @return role of the user
     */
    public static Role getUserRole(DBCachePool pool, User user) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "select role from ROLES where id = ?"
            );
            statement.setInt(1, user.getId());
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Role.valueOf(resultSet.getString(1));
            }
            return null;
        } catch (SQLException e) {
            logger.error("Get user's role failed", e);
            return null;
        } finally {
            pool.putConnection(connection);
        }
    }

    /**
     * Changes a role of some user.
     * @param pool database connection pool
     * @param user whose role needs to be changed
     * @param role new role
     * @return true if successfully
     */
    public static boolean addOrUpdateRole(DBCachePool pool, User user, Role role) {
        Connection connection = null;
        try {
            connection = pool.getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "delete from ROLES where id = ?"
            );
            statement.setInt(1, user.getId());
            statement.executeUpdate();
            statement = connection.prepareStatement(
                    "insert into ROLES values (?, ?)"
            );
            statement.setInt(1, user.getId());
            statement.setString(2, role.name());
            statement.executeUpdate();
        } catch (SQLException e) {
            logger.error("Can't add new role", e);
        } finally {
            pool.putConnection(connection);
        }
        return false;
    }
}
