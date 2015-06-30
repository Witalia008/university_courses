import org.junit.Assert;

import java.io.IOException;

/**
 * Created by Witalia on 23.10.2014.
 */
public class TestSerialization {
    @org.junit.Test
    public void testCommunicationBetweenServerAndClient() throws Exception {
        Server server = new Server();
        Client client = new Client();
        new Thread() {
            @Override
            public void run() {
                try {
                    server.init(27015);
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        }.start();
        client.init("127.0.0.1", 27015);

        Employee employee = new Employee(15, "Name");
        client.sendObject(employee);

        Assert.assertEquals("Server received incorrect data",
                employee.toString(),
                ((Employee) server.receiveObject()).toString());

        server.sendObject(employee);

        Assert.assertEquals("Client received incorrect data",
                employee.toString(),
                ((Employee) client.receiveObject()).toString());

    }
}
