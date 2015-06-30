package dbtools;

import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

/**
 * Connection pool to a database.
 * Created by Witalia on 21.11.2014.
 */
public class DBCachePool {
    private static Logger logger = Logger.getLogger(DBCachePool.class);

    /**
     * Number of initial connections.
     */
    private static final int INITIAL_CONNECTIONS = 10;

    /**
     * URL for connection to a database.
     */
    private String url;
    private String username;
    private String password;

    /**
     * Cache of connections.
     */
    private BlockingQueue<Connection> connections
            = new ArrayBlockingQueue<>(INITIAL_CONNECTIONS);

    /**
     * Single instance
     */
    private static DBCachePool instance;

    /**
     * Loads a database driver and initializes
     * {@Link INITIAL_CONNECTIONS} connections to database.
     * @param url
     * @param username
     * @param password
     * @throws SQLException
     */
    private DBCachePool(String url, String username, String password)
            throws SQLException {
        this.url = url;
        this.username = username;
        this.password = password;
        try {
            Class.forName("oracle.jdbc.driver.OracleDriver");
        } catch (ClassNotFoundException ex) {
            logger.fatal("Database driver not found", ex);
        }

        for (int i = 0; i < INITIAL_CONNECTIONS; ++i) {
            connections.add(newConnection());
        }
    }

    public static DBCachePool getInstance() {
        if (instance == null) {
            try {
                instance = new DBCachePool(
                        "jdbc:oracle:thin:@localhost:1521:xe",
                        "Witalia", "password");
            } catch (SQLException e) {
                logger.fatal("Can't create instance of pool", e);
            }
        }
        return instance;
    }

    /**
     * Gets connection from cache when possible or opens new one.
     * @return connection to a database
     * @throws SQLException
     */
    public synchronized Connection getConnection() throws SQLException {
        if (connections.size() == 0) {
            putConnection(newConnection());
        }
        return connections.poll();
    }

    /**
     * Opens new connection to a database.
     * @return
     * @throws SQLException
     */
    private Connection newConnection() throws SQLException {
        return new MyConnection(DriverManager.getConnection(
                url, username, password
        ));
    }

    /**
     * Put connection into cache for future use
     * @param c supposed free connection
     */
    public void putConnection(Connection c) {
        if (c == null) {
            return;
        }
        try {
            connections.put(c);
        } catch (InterruptedException e) {
            logger.error("Thread was interrupted " +
                    "whilst putting connection into queue", e);
        }
    }
}
