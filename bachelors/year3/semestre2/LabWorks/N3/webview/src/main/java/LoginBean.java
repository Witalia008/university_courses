import org.apache.activemq.ActiveMQConnectionFactory;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.jms.*;
import java.io.Serializable;

/**
 * Created by Witalia on 26.03.2015.
 */
@ManagedBean
@SessionScoped
public class LoginBean implements Serializable {
    private static ConnectionFactory connectionFactory =
            new ActiveMQConnectionFactory("admin", "admin", "tcp://localhost:61616");

    private String username;
    private String password;
    private boolean newUser;

    public String getUsername() {
        return username;
    }
    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }
    public void setPassword(String password) {
        this.password = password;
    }

    public boolean isNewUser() {
        return newUser;
    }
    public void setNewUser(boolean newUser) {
        this.newUser = newUser;
    }

    public String submit() {
        Connection connection = null;
        try {
            connection = connectionFactory.createConnection();
            connection.start();

            Session session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);

            Destination destination = session.createQueue("queue.queue_in");
            MessageProducer producer = session.createProducer(destination);
            producer.setDeliveryMode(DeliveryMode.NON_PERSISTENT);

            destination = session.createQueue("queue.queue_out");
            MessageConsumer consumer = session.createConsumer(destination);

            TextMessage msg = session.createTextMessage(username);
            producer.send(msg);
            TextMessage response = (TextMessage) consumer.receive();
            username = response.getText();
        } catch (JMSException e) {
            username = e.getMessage();
            e.printStackTrace();
        }

        return "success";
    }
}
