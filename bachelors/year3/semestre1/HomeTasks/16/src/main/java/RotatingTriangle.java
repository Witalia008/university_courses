import javax.swing.*;
import java.awt.*;
import java.util.Observable;
import java.util.Observer;

/**
 * Created by Witalia on 26.11.2014.
 */
public class RotatingTriangle
        extends Thread
        implements Observer {

    private Point pos = null;
    private double angle = 0;
    private double delta = 0.1;
    private int radius = 40;
    private boolean interrupted = false;

    public double getAngle() {
        return angle;
    }

    public RotatingTriangle(Point pos) {
        this.pos = pos;
    }

    @Override
    public void update(Observable o, Object arg) {
        angle = (Double)arg;
    }

    @Override
    public void run() {
        while (!isInterrupted()) {
            angle += delta;
            if (angle > Math.PI) {
                angle -= Math.PI;
            }
            try {
                this.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void interrupt() {
        interrupted = true;
    }

    @Override
    public boolean isInterrupted() {
        return interrupted;
    }

    public void paint(Graphics g) {
        int[] x = new int[3];
        int[] y = new int[3];
        for (int i = 0; i < 3; i++) {
            double curAngle = angle + Math.PI / 2 + (2 * i) * Math.PI / 3;
            x[i] = pos.x + (int) (Math.cos(curAngle) * radius);
            y[i] = pos.y + (int) (Math.sin(curAngle) * radius);
        }
        g.setColor(Color.BLACK);
        g.fillPolygon(x, y, 3);
        /*g.setColor(Color.BLUE);
        g.drawString(String.format("%1.3f", angle), pos.x, pos.y);*/
    }
}