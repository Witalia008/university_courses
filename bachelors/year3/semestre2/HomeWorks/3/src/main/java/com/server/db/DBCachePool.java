package com.server.db;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

/**
 * Created by Witalia on 28.01.2015.
 */
public class DBCachePool {
    private static final int INITIAL_CONNECTIONS = 10;

    private String url;
    private String username;
    private String password;

    private BlockingQueue<Connection> connections
            = new ArrayBlockingQueue<>(INITIAL_CONNECTIONS);

    private static DBCachePool instance;

    private DBCachePool(String url, String username, String password) throws SQLException {
        this.url = url;
        this.username = username;
        this.password = password;

        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }

        for (int i = 0; i < INITIAL_CONNECTIONS; i++) {
            connections.add(newConnection());
        }
    }

    public synchronized static DBCachePool getInstance() {
        if (instance == null) {
            try {
                instance = new DBCachePool(
                        "jdbc:mysql://localhost:3306/oop_c3_ii_hw3",
                        "user", "password");
            } catch (SQLException e) {
                e.printStackTrace();
        }
        }
        return instance;
    }

    private Connection newConnection() throws SQLException {
        return new MyConnection(DriverManager.getConnection(url, username, password));
    }

    public synchronized Connection getConnection() throws SQLException {
        if (connections.size() == 0) {
            putConnection(newConnection());
        }
        return connections.poll();
    }

    public void putConnection(Connection connection) {
        if (connection == null) {
            return;
        }
        try {
            connections.put(connection);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
