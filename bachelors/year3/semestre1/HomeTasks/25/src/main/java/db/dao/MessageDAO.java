package db.dao;

import db.beans.Message;
import db.beans.Room;
import db.beans.User;

import java.sql.SQLException;
import java.util.Collection;

/**
 * Created by Witalia on 09.12.2014.
 */
public interface MessageDAO {
    public void addMessage(Message message) throws SQLException;
    public Collection getMessagesByRoom(Room room) throws SQLException;
    public Collection getMessagesByUser(User user) throws SQLException;
}
