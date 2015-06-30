import com.ibm.mq.*;

import java.io.IOException;

/**
 * Created by Witalia on 25.03.2015.
 */
public class Client {
    private MQQueueManager QM = null;
    private MQQueue Qinp = null;
    private MQQueue Qout = null;

    public Client(String QMName, String IP, int port,
                      String channel, String inpQName, String outQName) throws MQException {
        MQEnvironment.hostname = null;
//        MQEnvironment.hostname = IP;
//        MQEnvironment.port = port;
//        MQEnvironment.channel = channel;
//        MQEnvironment.CCSID = 866;

        QM = new MQQueueManager(QMName);
        Qinp = QM.accessQueue(inpQName, MQC.MQOO_INPUT_EXCLUSIVE);
        Qout = QM.accessQueue(outQName, MQC.MQOO_OUTPUT);
    }

    public void disconnect() throws MQException {
        Qinp.close();
        Qout.close();
        QM.disconnect();
    }

    private void sendQuery(String query) throws IOException, MQException {
        MQMessage msg = new MQMessage();
        msg.writeString(query);
        Qout.put(msg);
    }

    public boolean printResult() {
        try {
            MQMessage resp = new MQMessage();
            Qinp.get(resp);
            System.out.println(resp.readLine());
            return true;
        } catch (MQException | IOException e) {
            return false;
        }
    }

    public static void main1() throws IOException, MQException {
        Client client = new Client("StockQM", "localhost", 1414,
                "SYSTEM.DEF.SVRCONN", "responses", "requests");

        client.sendQuery("1#Vegetables");
        client.sendQuery("2#Cabbage#1.1#10#0#11");
        client.sendQuery("3#2");
        client.sendQuery("4#3");
        client.sendQuery("5");

        client.disconnect();
    }

    public static void main2() throws IOException, MQException {
        Client client = new Client("StockQM", "localhost", 1414,
                "SYSTEM.DEF.SVRCONN", "responses", "requests");

        while (client.printResult());
    }

    public static void main(String[] args) throws IOException, MQException {
        main1();
    }
}
