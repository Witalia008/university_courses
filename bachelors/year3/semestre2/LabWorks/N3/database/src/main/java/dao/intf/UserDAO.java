package dao.intf;

import beans.User;

import java.sql.SQLException;

/**
 * Created by Witalia on 04.04.2015.
 */
public interface UserDAO {
    public void addUser(User user) throws SQLException;
    public User getUserById(Integer userID) throws SQLException;
    public User getUserByUsername(String username) throws SQLException;
}
