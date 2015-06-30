package univ.c3.II.oop.server;

import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

/**
 * Created by witalia on 14.12.14.
 */

/**
 * @ServerEndpoint gives the relative name for the end point
 */
@ServerEndpoint(value = "/geosvc",
                configurator = GetHttpSessionConfigurator.class)
public class GeoService {
    private String rootFolder;
    private String dataFolder = "resources\\data\\";

    @OnOpen
    public void onOpen(Session session, EndpointConfig config) {
        System.out.println(session.getId() + " has opened a connection.");
        rootFolder = config.getUserProperties().get("ServletRealPath") + "\\";
    }

    @OnMessage
    public void onMessage(String message, Session session) {
        float sonicSpeed = Float.parseFloat(message);

        float[] pts = new PointData(sonicSpeed)
                .initialize(rootFolder + dataFolder + "data1.txt").getRes();

        System.out.println("Message from " + session.getId() + ": " + message);
        try {
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
