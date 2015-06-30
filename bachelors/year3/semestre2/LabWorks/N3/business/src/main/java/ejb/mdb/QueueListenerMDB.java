package ejb.mdb;

import asp.LoggableMethod;
import org.jboss.annotation.ejb.ResourceAdapter;

import javax.annotation.Resource;
import javax.ejb.ActivationConfigProperty;
import javax.ejb.EJBException;
import javax.ejb.MessageDriven;
import javax.jms.*;

/**
 * Created by Witalia on 28.03.2015.
 */
@MessageDriven(activationConfig = {
        @ActivationConfigProperty(
                propertyName = "acknowledgeMode", propertyValue = "Auto-acknowledge"),
        @ActivationConfigProperty(
                propertyName = "destinationType", propertyValue = "javax.jms.Queue"),
        @ActivationConfigProperty(
                propertyName = "destination", propertyValue = "queue.queue_in")
})
@ResourceAdapter("activemq-ra.rar")
public class QueueListenerMDB implements MessageListener {
    @Resource(mappedName = "java:/activemq/ConnectionFactory")
    private ConnectionFactory connectionFactory;
    @Resource(mappedName = "java:/activemq/queue_out")
    private Destination queue;
    private Connection connection;

    public void init() throws JMSException {
        connection = connectionFactory.createConnection();
        connection.start();
    }

    public void destroy() throws JMSException {
        connection.close();
    }

    private void sendMessage(String text) throws JMSException {
        Session session = null;
        MessageProducer sender = null;
        try {
            session = connection.createSession(true, Session.AUTO_ACKNOWLEDGE);
            sender = session.createProducer(queue);
            sender.setDeliveryMode(DeliveryMode.PERSISTENT);

            TextMessage response = session.createTextMessage(text);
            sender.send(response);
        } finally {
            try {
                if (sender != null) {
                    sender.close();
                }
            } finally {
                if (session != null) {
                    session.close();
                }
            }
        }
    }

    @LoggableMethod
    @Override
    public void onMessage(Message message) {
        try {
            init();
            String text = ((TextMessage) message).getText();
            System.out.println(text);
            sendMessage("Response for '" + text + "'");
        } catch (JMSException e) {
            e.printStackTrace();
        } finally {
            try {
                destroy();
            } catch (JMSException e) {
                throw new EJBException("Error in closing connection", e);
            }
        }
    }
}
