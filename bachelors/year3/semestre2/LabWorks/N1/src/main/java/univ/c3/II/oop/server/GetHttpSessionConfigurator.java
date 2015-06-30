package univ.c3.II.oop.server;

import javax.servlet.http.HttpSession;
import javax.websocket.HandshakeResponse;
import javax.websocket.server.HandshakeRequest;
import javax.websocket.server.ServerEndpointConfig;

/**
 * Created by Witalia on 04.02.2015.
 */
public class GetHttpSessionConfigurator extends ServerEndpointConfig.Configurator {
    @Override
    public void modifyHandshake(ServerEndpointConfig config,
                                HandshakeRequest request,
                                HandshakeResponse response) {
        HttpSession httpSession = (HttpSession) request.getHttpSession();
        System.out.println("Handshake");
        if (httpSession == null) {
            System.out.println("Session is null");
        } else if (httpSession.getServletContext() == null) {
            System.out.println("Context is null");
        } else {
            System.out.println(httpSession.getServletContext().getRealPath(""));
            System.out.println(httpSession.getId());
            config.getUserProperties().put("ServletRealPath", httpSession.getServletContext().getRealPath(""));
        }
    }
}
