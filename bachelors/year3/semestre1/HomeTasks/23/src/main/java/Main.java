import javax.swing.*;
import java.awt.*;
import java.util.Random;

/**
 * Created by Witalia on 23.10.2014.
 */
public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new Main().createAndRunGUI();
            }
        });
    }

    public static void createAndRunGUI() {
        JFrame frame = new JFrame("23");
        Dimension size = new Dimension(500, 300);
        frame.setLayout(null);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.getContentPane().setPreferredSize(size);
        frame.setResizable(false);

        MyPanel panel = new MyPanel();
        panel.setBounds(0, 0, size.width, size.height);
        panel.setPoint(
                new PointMover(
                        new Rectangle(0, 0, size.width, size.height),
                        true,
                        panel
                )
        );

        frame.add(panel);

        frame.pack();
        frame.setVisible(true);
    }
}

class MyPanel extends JPanel {
    private PointMover point;
    private Color pointColor;

    public void setPoint(PointMover point) {
        this.point = point;
        Random rand = new Random();
        pointColor = new Color(
                rand.nextFloat(),
                rand.nextFloat(),
                rand.nextFloat()
        );
        point.start();
    }

    @Override
    protected void paintComponent(Graphics g) {
        g.setColor(Color.white);
        g.fillRect(0, 0, this.getWidth(), this.getHeight());
        if (point != null) {
            point.drawPoint(g, pointColor);
        }
    }
}
