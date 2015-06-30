package db.dao.impl;

import db.beans.Room;
import db.dao.RoomDAO;
import db.hb.HibernateSessionManager;
import org.hibernate.Session;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * Created by Witalia on 09.12.2014.
 */
public class RoomDAOImpl implements RoomDAO {
    @Override
    public void addRoom(Room room) throws SQLException {
        Session session = null;
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            session.beginTransaction();
            session.save(room);
            session.getTransaction().commit();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
    }

    @Override
    public Room getRoomById(Integer roomId) throws SQLException {
        Session session = null;
        Room room = null;
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            room = (Room) session.get(Room.class, roomId);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
        return room;
    }

    @Override
    public Collection getAllRooms() throws SQLException {
        Session session = null;
        List rooms = new ArrayList<Room>();
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            rooms = session.createCriteria(Room.class).list();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
        return rooms;
    }
}
