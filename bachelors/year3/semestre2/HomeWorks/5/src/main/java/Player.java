import org.apache.activemq.ActiveMQConnectionFactory;

import javax.jms.*;
import java.util.Arrays;
import java.util.Scanner;

/**
 * Created by Witalia on 02.02.2015.
 */
public class Player implements ExceptionListener, Runnable {
    private String name;
    private Player opponent;
    private char move;
    private char[][] field = new char[3][3];
    private Scanner in = new Scanner(System.in);
    private Thread thread;

    private final ActiveMQConnectionFactory connectionFactory;
    private Connection connection;
    private Session session;

    private MessageConsumer consumer;
    private MessageProducer producer;

    public Player(String name, char move) {
        this.name = name;
        this.move = move;
        // Create a ConnectionFactory
        connectionFactory = new ActiveMQConnectionFactory("vm://localhost");
    }

    public boolean setOpponent(Player opponent) {
        if (this.name.equals(opponent.name) || this.move == opponent.move) {
            return false;
        }
        if (this.opponent == opponent) {
            return true;
        }
        thread = new Thread() {
            @Override
            public void run() {
                try {
                    // Create a Connection
                    connection = connectionFactory.createConnection();
                    connection.start();

                    // Create a Session
                    session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);

                    // Create Producer
                    Destination destination = session.createQueue(name);
                    producer = session.createProducer(destination);
                    producer.setDeliveryMode(DeliveryMode.NON_PERSISTENT);

                    // Create Consumer
                    destination = session.createQueue(opponent.name);
                    consumer = session.createConsumer(destination);

                } catch (JMSException e) {
                    e.printStackTrace();
                }
            }
        };
        thread.start();

        this.opponent = opponent;
        opponent.setOpponent(this);
        try {
            thread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return true;
    }

    @Override
    protected void finalize() throws Throwable {
        new Thread() {
            @Override
            public void run() {
                try {
                    consumer.close();
                    session.close();
                    connection.close();
                } catch (JMSException e) {
                    e.printStackTrace();
                }
            }
        }.start();
        super.finalize();
    }

    @Override
    public synchronized void onException(JMSException e) {
        e.printStackTrace();
    }

    private void addMove(String m, char q) {
        String[] a = m.split(":");
        int x = Integer.parseInt(a[0]);
        int y = Integer.parseInt(a[1]);
        field[x][y] = q;
    }

    private void makeMove() {
        outputField();
        String curMove = null;
        do {
            System.out.println(name);
            System.out.println("Enter move in format x:y");
            curMove = in.next();
        } while (!validMove(curMove));
        addMove(curMove, move);
        sendMove(curMove);
    }

    private boolean validMove(String curMove) {
        String[] a = curMove.split(":");
        int x = Integer.parseInt(a[0]);
        int y = Integer.parseInt(a[1]);
        return x >= 0 && y >= 0 && x < 3 && y < 3 && field[x][y] == '.';
    }

    private void sendMove(String curMove) {
        try {
            TextMessage message = session.createTextMessage(curMove);
            producer.send(message);
        } catch (JMSException e) {
            e.printStackTrace();
        }
    }

    private String receiveMove() {
        try {
            TextMessage message = (TextMessage) consumer.receive();
            return message.getText();
        } catch (JMSException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void run() {
        resetField();
        for (int i = 0; !isEnd(); ++i) {
            if (i % 2 == (move == 'X' ? 0 : 1)) {
                makeMove();
            } else {
                addMove(receiveMove(), opponent.move);
                if (isEnd()) {
                    System.out.println(opponent.name + " won!");
                    outputField();
                    break;
                }
            }
        }
//        System.out.println(name);
    }

    private boolean isEnd() {
        for (int i = 0; i < 3; i++) {
            if (field[i][0] == field[i][1] && field[i][0] == field[i][2] && field[i][0] != '.'
                    || field[0][i] == field[1][i] && field[0][i] == field[2][i] && field[0][i] != '.') {
                return true;
            }
        }
        return field[1][1] != '.' && (field[2][2] == field[0][0] && field[0][0] == field[1][1] ||
                field[0][2] == field[1][1] && field[2][0] == field[1][1]);
    }

    private void resetField() {
        for (int i = 0; i < field.length; i++) {
            Arrays.fill(field[i], '.');
        }
    }

    private void outputField() {
        for (int i = 0; i < field.length; i++) {
            for (int j = 0; j < field[i].length; j++) {
                System.out.print(field[i][j]);
            }
            System.out.println();
        }
    }
}
