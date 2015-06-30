import org.apache.activemq.ActiveMQConnectionFactory;

import javax.jms.*;

/**
 * Created by Witalia on 01.02.2015.
 */
public class Main {
    public static void main(String[] args) throws InterruptedException {
        Player player1 = new Player("Player-1", 'X');
        Player player2 = new Player("Player-2", 'O');
        player1.setOpponent(player2);
        Thread thread1 = new Thread(player1);
        Thread thread2 = new Thread(player2);
        thread1.start();
        thread2.start();
        thread1.join();
        thread2.join();
//        System.out.println("---");
    }
}