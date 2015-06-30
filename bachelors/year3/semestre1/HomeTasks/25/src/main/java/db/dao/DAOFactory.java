package db.dao;

import db.dao.impl.MessageDAOImpl;
import db.dao.impl.RoomDAOImpl;
import db.dao.impl.UserDAOImpl;

/**
 * Created by Witalia on 09.12.2014.
 */
public class DAOFactory {
    private static DAOFactory daoFactory;
    private static UserDAO userDAO;
    private static MessageDAO messageDAO;
    private static RoomDAO roomDAO;

    private static synchronized DAOFactory getInstance() {
        if (daoFactory == null) {
            daoFactory = new DAOFactory();
        }
        return daoFactory;
    }

    public static synchronized UserDAO getUserDAO() {
        if (userDAO == null) {
            userDAO = new UserDAOImpl();
        }
        return userDAO;
    }

    public static synchronized MessageDAO getMessageDAO() {
        if (messageDAO == null) {
            messageDAO = new MessageDAOImpl();
        }
        return messageDAO;
    }

    public static synchronized RoomDAO getRoomDAO() {
        if (roomDAO == null) {
            roomDAO = new RoomDAOImpl();
        }
        return roomDAO;
    }
}
