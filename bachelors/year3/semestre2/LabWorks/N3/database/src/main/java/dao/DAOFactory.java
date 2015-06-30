package dao;

import dao.impl.*;
import dao.intf.*;

/**
 * Created by Witalia on 04.04.2015.
 */
public class DAOFactory {
    private static DAOFactory factory;
    private UserDAO userDAO;
    private CarDAO carDAO;
    private OrderDAO orderDAO;
    private BillDAO billDAO;
    private RoleDAO roleDAO;

    private DAOFactory() {}

    public static synchronized DAOFactory getFactory() {
        if (factory == null) {
            factory = new DAOFactory();
        }
        return factory;
    }

    public synchronized UserDAO getUserDAO() {
        if (userDAO == null) {
            userDAO = new UserDAOImpl();
        }
        return userDAO;
    }

    public synchronized CarDAO getCarDAO() {
        if (carDAO == null) {
            carDAO = new CarDAOImpl();
        }
        return carDAO;
    }

    public synchronized OrderDAO getOrderDAO() {
        if (orderDAO == null) {
            orderDAO = new OrderDAOImpl();
        }
        return orderDAO;
    }

    public synchronized BillDAO getBillDAO() {
        if (billDAO == null) {
            billDAO = new BillDAOImpl();
        }
        return billDAO;
    }

    public synchronized RoleDAO getRoleDAO() {
        if (roleDAO == null) {
            roleDAO = new RoleDAOImpl();
        }
        return roleDAO;
    }
}
