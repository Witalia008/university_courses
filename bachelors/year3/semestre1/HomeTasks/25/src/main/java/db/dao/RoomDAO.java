package db.dao;

import db.beans.Room;

import java.sql.SQLException;
import java.util.Collection;

/**
 * Created by Witalia on 09.12.2014.
 */
public interface RoomDAO {
    public void addRoom(Room room) throws SQLException;
    public Room getRoomById(Integer roomId) throws SQLException;
    public Collection getAllRooms() throws SQLException;
}
