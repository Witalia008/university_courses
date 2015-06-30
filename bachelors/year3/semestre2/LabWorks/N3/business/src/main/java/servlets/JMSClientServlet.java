package servlets;

import dao.DAOFactory;
import hb.HibernateSessionManager;

import javax.jms.*;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * Created by Witalia on 29.03.2015.
 */
public class JMSClientServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String destinationName = "java:/activemq/queue_in";
        PrintWriter out = resp.getWriter();
        Context ic = null;
        ConnectionFactory cf = null;
        Connection connection =  null;

        try {
            ic = new InitialContext();

            cf = (ConnectionFactory)ic.lookup("java:/activemq/ConnectionFactory");
            Queue queue = (Queue)ic.lookup(destinationName);

            connection = cf.createConnection("admin", "admin");
            Session session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
            MessageProducer publisher = session.createProducer(queue);

            connection.start();

            TextMessage message = session.createTextMessage("Hello AS 7 !");
            publisher.send(message);

            out.println("Message sent to the JMS Provider");

            out.println(DAOFactory.getFactory()
                    .getUserDAO().getUserByUsername("user")
                    .getPassword());
        }
        catch (Exception exc) {
            exc.printStackTrace();
        }
        finally {


            if (connection != null)   {
                try {
                    connection.close();
                } catch (JMSException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req, resp);
    }
}
