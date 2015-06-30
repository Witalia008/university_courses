import org.apache.mina.core.RuntimeIoException;
import org.apache.mina.core.future.IoFuture;
import org.apache.mina.core.future.IoFutureListener;
import org.apache.mina.core.service.IoConnector;
import org.apache.mina.core.service.IoHandler;
import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IoSession;

import java.net.InetSocketAddress;
import java.net.SocketAddress;

/**
 * Created by Witalia on 01.02.2015.
 */
public class ClientToProxyIoHandler extends AbstractProxyIoHandler {
    private final ServerToProxyIoHandler connectorHandler = new ServerToProxyIoHandler();
    private final IoConnector connector;
    private final SocketAddress remoteAddress;

    public ClientToProxyIoHandler(IoConnector connector, SocketAddress remoteAddress) {
        this.connector = connector;
        this.remoteAddress = remoteAddress;
        connector.setHandler(connectorHandler);
    }

    @Override
    public void sessionOpened(IoSession session) throws Exception {
        connector.connect(remoteAddress).addListener(new IoFutureListener<IoFuture>() {
            @Override
            public void operationComplete(IoFuture ioFuture) {
                try {
                    IoSession session1 = ioFuture.getSession();
                    session1.setAttribute(OTHER_IO_SESSION, session);
                    session.setAttribute(OTHER_IO_SESSION, session1);
                    session1.resumeRead();
                    session1.resumeWrite();
                } catch (RuntimeIoException ex) {
                    ex.printStackTrace();
                    session.close(true);
                } finally {
                    session.resumeRead();
                    session.resumeWrite();
                }
            }
        });
    }
}
