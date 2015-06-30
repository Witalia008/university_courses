import org.apache.mina.core.service.IoConnector;
import org.apache.mina.transport.socket.nio.NioSocketAcceptor;
import org.apache.mina.transport.socket.nio.NioSocketConnector;

import java.io.IOException;
import java.net.InetSocketAddress;

/**
 * Created by Witalia on 29.01.2015.
 */
public class Main {
    private static final int PORT = 12345;

    public static void main(String[] args) throws IOException {
        NioSocketAcceptor acceptor = new NioSocketAcceptor();
        IoConnector connector = new NioSocketConnector();

        connector.setConnectTimeoutMillis(30 * 1000L);

        ClientToProxyIoHandler handler = new ClientToProxyIoHandler(connector,
                new InetSocketAddress("www.google.com", 80));

        acceptor.setHandler(handler);
        acceptor.bind(new InetSocketAddress(PORT));

        System.out.println("Listening on port " + PORT);
    }
}
