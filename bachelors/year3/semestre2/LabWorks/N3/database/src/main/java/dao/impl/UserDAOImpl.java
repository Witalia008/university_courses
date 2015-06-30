package dao.impl;

import beans.User;
import dao.intf.UserDAO;
import hb.HibernateSessionManager;
import org.hibernate.Session;
import org.hibernate.criterion.Restrictions;

import java.sql.SQLException;
import java.util.List;

/**
 * Created by Witalia on 04.04.2015.
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
        } finally {
            HibernateSessionManager.closeSession(session);
        }
    }

    @Override
    public User getUserById(Integer userID) throws SQLException {
        User user = null;
        Session session = null;
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            user = (User) session.get(User.class, userID);
        } finally {
            HibernateSessionManager.closeSession(session);
        }
        return user;
    }

    @Override
    public User getUserByUsername(String username) throws SQLException {
        Session session = null;
        List<User> users = null;
        try {
            session = HibernateSessionManager.getSessionFactory().openSession();
            users = session.createCriteria(User.class)
                    .add(Restrictions.eq("name", username)).list();
        } finally {
            HibernateSessionManager.closeSession(session);
        }
        return users != null && users.size() > 0 ? users.get(0) : null;
    }
}
