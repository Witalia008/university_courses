import com.ibm.mq.*;

import java.io.IOException;
import java.util.Arrays;

/**
 * Created by Witalia on 25.03.2015.
 */
public class Server {
    private MQQueueManager QM = null;
    private MQQueue Qinp = null;
    private MQQueue Qout = null;
    private Stock stock;

    public void start(String QMName, String IP, int port,
                      String channel, String inpQName, String outQName) throws MQException {
        MQEnvironment.hostname = null;
//        MQEnvironment.hostname = IP;
//        MQEnvironment.port = port;
//        MQEnvironment.channel = channel;
//        MQEnvironment.CCSID = 866;

        QM = new MQQueueManager(QMName);
        Qinp = QM.accessQueue(inpQName, MQC.MQOO_INPUT_AS_Q_DEF);
        Qout = QM.accessQueue(outQName, MQC.MQOO_OUTPUT);

        stock = new Stock();
        int i = 0;
        while (processQuery()) ++i;
        Qinp.close(); Qout.close();
        QM.disconnect();
        stock.close();
    }

    private boolean processQuery() {
        try {
            MQGetMessageOptions gmo = new MQGetMessageOptions();
            gmo.options = MQC.MQGMO_WAIT;
            gmo.waitInterval = 3000;
            MQMessage req = new MQMessage();
            Qinp.get(req, gmo);
            MQMessage resp = new MQMessage();

            String query = req.readLine();
            if (query == null) {
                return false;
            }
            String[] params = query.split("#");
            for (int i = 0; i < params.length; i++) {
                if (params[i].equals("~")) {
                    params[i] = null;
                }
            }
            System.out.println(Arrays.toString(params));
            try {
                switch (params[0]) {
                    case "1":
                        resp.writeString(query + "#0#Add Category#" + stock.addCategory(params[1]));
                        break;
                    case "2":
                        resp.writeString(query + "#0#Add Product#" +
                                stock.addProduct(
                                        params[1],
                                        Double.parseDouble(params[2]),
                                        Integer.parseInt(params[3]),
                                        Integer.parseInt(params[4]),
                                        Integer.parseInt(params[5])
                                ));
                        break;
                    case "3":
                        resp.writeString(query + "#0#Delete Product#" +
                                stock.deleteProduct(Integer.parseInt(params[1])));
                        break;
                    case "4":
                        resp.writeString(query + "#0#Product by category#" + stock.getProducts(Integer.parseInt(params[1])));
                        break;
                    case "5":
                        resp.writeString(query + "#0#Categories#" + stock.getCategory());
                        break;
                }
            } catch (Throwable e) {
                e.printStackTrace();
                resp.writeString(query + "#1#" + e.getMessage());
            }
            // set resp here
            Qout.put(resp);
            return true;
        } catch (MQException | IOException e) {
            return false;
        }
    }

    public static void main(String[] args) throws MQException, IOException {
        Server server = new Server();
        server.start("StockQM", "localhost", 1414, "SYSTEM.DEF.SVRCONN", "requests", "responses");
    }
}
