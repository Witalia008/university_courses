import javax.swing.*;
import java.awt.*;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.File;
import java.util.Random;

/**
 * Created by Witalia on 23.10.2014.
 */
public class Main {
    public static final String PATH_TO_FILES = "target\\classes\\data\\";
    private MoveProcessor processor;
    private JFrame frame;
    private Dimension size;
    private JLabel imageLabel;
    private JComboBox comboBox;

    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new Main().createAndShowGui();
            }
        });
    }

    public String[] getComboBoxItems() {
        String[] res = new String[comboBox.getItemCount()];
        for (int i = 0; i < res.length; i++) {
            res[i] = comboBox.getItemAt(i).toString();
        }
        return res;
    }

    public void createAndShowGui() {
        frame = new JFrame("24");
        frame.setLayout(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        size = new Dimension(700, 500);
        frame.getContentPane().setPreferredSize(size);
        frame.setResizable(false);

        imageLabel = new JLabel();

        comboBox = new JComboBox(getImageFiles());
        comboBox.setBounds(0, 0, size.width, 30);

        comboBox.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                if (e.getStateChange() == ItemEvent.DESELECTED)
                    return;
                ImageIcon img = new ImageIcon(PATH_TO_FILES + e.getItem());
                imageLabel.setIcon(img);
                imageLabel.setBounds(0, 0, img.getIconWidth(), img.getIconHeight());
                if (processor != null) {
                    processor.end();
                }
                processor = new MoveProcessor(
                        new Rectangle(
                                0,
                                comboBox.getHeight(),
                                size.width - img.getIconWidth(),
                                size.height
                                        - img.getIconHeight() - comboBox.getHeight()
                        ),
                        imageLabel
                );
                processor.start();
            }
        });
        frame.getContentPane().add(comboBox);
        frame.getContentPane().add(imageLabel);

        frame.pack();
        frame.setVisible(true);
    }

    public static String[] getImageFiles() {
        return new File(PATH_TO_FILES).list();
    }
}