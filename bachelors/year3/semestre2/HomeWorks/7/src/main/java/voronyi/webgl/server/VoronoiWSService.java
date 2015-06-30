package voronyi.webgl.server;

import voronyi.webgl.server.serialize.ServerSerializator;
import voronyi.webgl.shared.Serializator;

import javax.websocket.OnClose;
import javax.websocket.OnMessage;
import javax.websocket.OnOpen;
import javax.websocket.Session;
import javax.websocket.server.ServerEndpoint;
import java.io.IOException;

/**
 * Created by witalia on 14.12.14.
 */
/**
 * @ServerEndpoint gives the relative name for the end point
 */
@ServerEndpoint(value = "/getDiagram")
public class VoronoiWSService {
    private final static Serializator SERIALIZATOR =
            new ServerSerializator();

    @OnOpen
    public void onOpen(Session session) {
        System.out.println(session.getId() + " has opened a connection.");
    }

    @OnMessage
    public void onMessage(String message, Session session) {
        float[] pts = new float[]{
                -1.0f, -1.0f,
                -1.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, -1.0f
        };
        System.out.println("Message from " + session.getId() + ": " + message);
        try {
//            System.out.println(SERIALIZATOR.serialize(pts));
//            session.getBasicRemote().sendText(SERIALIZATOR.serialize(pts));
            String[] arr = new String[pts.length];
            for (int i = 0; i < arr.length; i++) {
                arr[i] = "" + pts[i];
            }
            session.getBasicRemote().sendText(String.join(",", arr));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @OnClose
    public void onClose(Session session) {
        System.out.println("Session " + session.getId() + " has ended");
    }
}
