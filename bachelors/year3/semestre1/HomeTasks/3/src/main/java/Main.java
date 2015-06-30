import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * Created by Witalia on 03.12.2014.
 */
public class Main extends JFrame {
    public Main() throws HeadlessException, FileNotFoundException {
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setPreferredSize(new Dimension(700, 500));
        setLayout(new BorderLayout());

        String fld = "src\\main\\resources\\";
        JPanel panel = null;
        boolean isServer = JOptionPane.showConfirmDialog(this, "Are you server?") == JOptionPane.OK_OPTION;
        try {
            panel = GUICreater.createGUI(fld + "server.xml", fld + "client.xml", isServer);
        } catch (Exception e) {
            e.printStackTrace();
        }
        add(panel, BorderLayout.CENTER);
        setTitle(isServer ? "Server" : "Client");

        pack();
        setVisible(true);
    }

    public static void main(String[] args) throws FileNotFoundException {
        new Main();
    }
}
