import javax.swing.*;
import java.awt.*;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Observable;
import java.util.Random;

/**
 * Created by Witalia on 26.11.2014.
 */
public class Main extends Observable {
    private JFrame frame = null;
    private RotatingTriangle[] triangles = null;
    private Timer timer = null;

    public Main(String title, int nTriangles) {
        frame = new JFrame(title);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setPreferredSize(new Dimension(800, 500));

        Random random = new Random();
        triangles = new RotatingTriangle[nTriangles];
        for (int i = 0; i < triangles.length; i++) {
            triangles[i] = new RotatingTriangle(new Point(100 * (i % 7 + 1), 100 * (i / 7 + 1)));
            triangles[i].setPriority(random.nextInt(10) + 1);
            this.addObserver(triangles[i]);
            triangles[i].start();
        }

        JPanel panel = new MyPanel(triangles);
        frame.add(panel);

        // Sync timer
        timer = new Timer(5000, null);
        timer.setInitialDelay(100);
        timer.start();
        timer.addActionListener(e -> {
            double maxAngle = Arrays.asList(triangles).stream().max((a, b) ->
                            a.getAngle() > b.getAngle() ? 1 : -1
            ).get().getAngle();
            Arrays.asList(triangles).forEach(a -> System.out.print(a.getAngle() + " "));
            System.out.println(maxAngle);
            notifyObservers(maxAngle);
        });

        // Paint timer
        new Timer(100, e -> {
            frame.repaint();
        }).start();

        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new Main("Rotating triangles", 15);
        });
    }
}

class MyPanel extends JPanel {
    private RotatingTriangle[] triangles = null;

    public MyPanel(RotatingTriangle[] triangles) {
        this.triangles = triangles;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        for (RotatingTriangle cur : triangles) {
            cur.paint(g);
        }
    }
}
