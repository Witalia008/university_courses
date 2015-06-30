import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IoSession;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.nio.charset.Charset;

/**
 * Created by Witalia on 01.02.2015.
 */
public class AbstractProxyIoHandler extends IoHandlerAdapter {
    private static final Charset CHARSET = Charset.forName("UTF-8");
    public static final String OTHER_IO_SESSION = AbstractProxyIoHandler.class.getName()
            + ".OtherIoSession";
    private static final Logger LOGGER = LoggerFactory.getLogger(AbstractProxyIoHandler.class);

    @Override
    public void sessionCreated(IoSession session) throws Exception {
        session.suspendRead();
        session.suspendWrite();
    }

    @Override
    public void sessionClosed(IoSession session) throws Exception {
        if (session.getAttribute(OTHER_IO_SESSION) != null) {
            IoSession session1 = (IoSession) session.getAttribute(OTHER_IO_SESSION);
            session1.setAttribute(OTHER_IO_SESSION, null);
            session1.close(false);
            session.setAttribute(OTHER_IO_SESSION, null);
        }
}

    @Override
    public void messageReceived(IoSession session, Object message) throws Exception {
        IoBuffer rb = (IoBuffer) message;
        IoBuffer wb = IoBuffer.allocate(rb.remaining());
        rb.mark();
        wb.put(rb);
        wb.flip();
        ((IoSession) session.getAttribute(OTHER_IO_SESSION)).write(wb);
        rb.reset();
        LOGGER.info(rb.getString(CHARSET.newDecoder()));
    }
}
