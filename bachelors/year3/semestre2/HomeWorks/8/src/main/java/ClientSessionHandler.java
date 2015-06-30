import org.apache.log4j.Logger;
import org.apache.mina.core.session.IdleStatus;
import org.apache.mina.core.session.IoSession;

import java.io.File;
import java.nio.channels.FileChannel;

/**
 * Created by Witalia on 01.02.2015.
 */
public class ClientSessionHandler extends AbstractProxyIoHandler {
    private static final Logger LOGGER = Logger.getLogger(ClientSessionHandler.class);

    private File file;
    private FileChannel wChannel;
    private String cmd;

    public ClientSessionHandler(String cmd) {
        this.cmd = cmd;
    }

    @Override
    public void sessionCreated(IoSession session) throws Exception {
        LOGGER.debug("CLIENT - Session Created: " + session);
    }

    @Override
    public void sessionClosed(IoSession session) throws Exception {
        LOGGER.debug("CLIENT - Session Closed - closing result file if open");
        if (wChannel != null) {
            wChannel.close();
        }
    }

    @Override
    public void messageReceived(IoSession session, Object message) throws Exception {
    }

    @Override
    public void sessionIdle(IoSession session, IdleStatus status) throws Exception {
        if (session.isClosing()) {
            return;
        }
        LOGGER.debug("CLIENT - Session Idle");
    }

    @Override
    public void exceptionCaught(IoSession session, Throwable cause) throws Exception {
        LOGGER.debug("CLIENT - Exception Caught " + cause.toString());
        session.close(true);
    }
}
