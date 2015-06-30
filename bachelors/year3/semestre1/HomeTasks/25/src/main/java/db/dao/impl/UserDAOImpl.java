package db.dao.impl;

import db.beans.Room;
import db.beans.User;
import db.dao.UserDAO;
import db.hb.HibernateSessionManager;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.criterion.Restrictions;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * Created by Witalia on 09.12.2014.
 */
public class UserDAOImpl implements UserDAO {
    @Override
    public void addUser(User user) throws SQLException {
        Session session = null;
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            session.beginTransaction();
            session.save(user);
            session.getTransaction().commit();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
    }

    @Override
    public void updateUser(Integer userId, User user) throws SQLException {
        Session session = null;
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            session.beginTransaction();
            session.update(user);
            session.getTransaction().commit();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
    }

    @Override
    public User getUserById(Integer userId) throws SQLException {
        Session session = null;
        User user = null;
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            user = (User) session.get(User.class, userId);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
        return user;
    }

    @Override
    public User getUserByUsername(String username) throws SQLException {
        Session session = null;
        List users = new ArrayList<User>();
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            users = session.createCriteria(User.class)
                    .add(Restrictions.eq("username", username)).list();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
        return users.size() > 0 ? ((User) users.get(0)) : null;
    }

    @Override
    public Collection getUsersByRoom(Room room) throws SQLException {
        Session session = null;
        List users = new ArrayList<User>();
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            session.beginTransaction(); // begin hmmm
            Integer roomId = room.getId();
            Query query = session.createQuery("from User where room = :roomId")
                    .setInteger("roomId", roomId);
            users = query.list();
            session.getTransaction().commit(); // end hmmm
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
        return users;
    }
}
