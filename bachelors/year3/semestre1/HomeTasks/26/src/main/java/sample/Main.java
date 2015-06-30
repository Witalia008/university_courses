package sample;

import javax.swing.*;
import java.awt.*;

/**
 * Created by Witalia on 27.11.2014.
 */
public class Main extends JFrame {
    public Main() {
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setPreferredSize(new Dimension(800, 500));
        setLayout(new BorderLayout());

        PlayerPanel panel = new PlayerPanel();
        add(panel, BorderLayout.CENTER);

        pack();
        setVisible(true);


        JFileChooser fileChooser = new JFileChooser();
        if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            String mediaURL = fileChooser.getSelectedFile().getPath();
            panel.setMediaURL(mediaURL);
            panel.play();
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Main());
    }
}