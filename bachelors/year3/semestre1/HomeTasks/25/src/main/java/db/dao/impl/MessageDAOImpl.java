package db.dao.impl;

import db.beans.Message;
import db.beans.Room;
import db.beans.User;
import db.dao.MessageDAO;
import db.hb.HibernateSessionManager;
import org.hibernate.Query;
import org.hibernate.Session;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * Created by Witalia on 09.12.2014.
 */
public class MessageDAOImpl implements MessageDAO {
    @Override
    public void addMessage(Message message) throws SQLException {
        Session session = null;
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            session.beginTransaction();
            session.save(message);
            session.getTransaction().commit();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
    }

    @Override
    public Collection getMessagesByRoom(Room room) throws SQLException {
        Session session = null;
        List messages = new ArrayList<Message>();
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            session.beginTransaction(); // begin hmmm
            Integer roomId = room.getId();
            Query query = session.createQuery("from Message where room = :roomId")
                    .setInteger("roomId", roomId);
            messages = query.list();
            session.getTransaction().commit(); // end hmmm
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
        return messages;
    }

    @Override
    public Collection getMessagesByUser(User user) throws SQLException {
        Session session = null;
        List messages = new ArrayList<Message>();
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            session.beginTransaction(); // begin hmmm
            Integer userId = user.getId();
            Query query = session.createQuery("from Message where user = :userId")
                    .setInteger("userId", userId);
            messages = query.list();
            session.getTransaction().commit(); // end hmmm
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
        return messages;
    }
}
