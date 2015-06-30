import drawing.DrawablePanel;
import org.apache.commons.io.FileUtils;
import props.Props;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by Witalia on 08.12.2014.
 */
public class GUICreater {
    private static DrawablePanel drawPanel;
    private static final ActionListener drawListener = e -> {
        drawPanel.setCur(((JButton) e.getSource()).getText());
    };
    private static final ActionListener fileListener = e -> {
        JFileChooser fc = new JFileChooser();
        if (fc.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
            String filePath = fc.getSelectedFile().getAbsolutePath();
            if (((JButton) e.getSource()).getText().equals("load")) {
                drawPanel.read(filePath);
            } else {
                drawPanel.save(filePath);
            }
        }
    };
    private static final ActionListener colorListener = e -> {
        Color c = JColorChooser.showDialog(null, "Choose color", null);
        JButton btn = ((JButton) e.getSource());
        btn.setBackground(c);
        if (btn.getText().equals("bg")) {
            drawPanel.setBgCol(c);
        } else {
            drawPanel.setFgCol(c);
        }
    };

    private static final String[] buttons = {"ellipse", "line", "rect", "load", "save", "bg", "fg"};
    private static final ActionListener[] listeners = {
            drawListener, drawListener, drawListener,
            fileListener, fileListener,
            colorListener, colorListener
    };
    private static int width = 700;
    private static int height = 500;

    private static ServerSocket server;
    private static Socket client;

    public static JPanel createGUI(String sFile, String cFile, boolean isServer) throws IOException {
        InputStream xml;
        if (isServer) {
            server = new ServerSocket(27014);
            client = server.accept();
        } else {
            client = new Socket("127.0.0.1", 27014);
        }
        if (isServer) {
            xml = new FileInputStream(new File(sFile));
            FileUtils.copyFile(new File(cFile), client.getOutputStream());
            client.getOutputStream().flush();
            client.close();
        } else {
            xml = client.getInputStream();
        }

        System.out.println("1");
        Props props = new Props(xml);
        System.out.println("2");

        JPanel res = new JPanel(new BorderLayout());

        if (props.getValue("width") != null) {
            width = Integer.parseInt(props.getValue("width"));
        }
        if (props.getValue("height") != null) {
            height = Integer.parseInt(props.getValue("height"));
        }

        drawPanel = new DrawablePanel(width, height, isServer);

        JPanel btnPanel = new JPanel();
        for (int i = 0; i < buttons.length; i++) {
            String name = buttons[i];
            if (props.contains("button", name)) {
                JButton btn = new JButton(name);
                btn.addActionListener(listeners[i]);
                btnPanel.add(btn);
            }
        }

        res.add(btnPanel, BorderLayout.NORTH);
        res.add(drawPanel, BorderLayout.CENTER);

        return  res;
    }
}
