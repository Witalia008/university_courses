package db.dao;

import db.beans.Room;
import db.beans.User;

import java.sql.SQLException;
import java.util.Collection;

/**
 * Created by Witalia on 09.12.2014.
 */
public interface UserDAO {
    public void addUser(User user) throws SQLException;
    public void updateUser(Integer userId, User user) throws SQLException;
    public User getUserById(Integer userId) throws SQLException;
    public User getUserByUsername(String username) throws SQLException;
    public Collection getUsersByRoom(Room room) throws SQLException;
}
