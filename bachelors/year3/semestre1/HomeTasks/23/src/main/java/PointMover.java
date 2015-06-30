import java.awt.*;
import java.util.Random;

/**
 * Created by Witalia on 23.10.2014.
 */
class PointMover extends Thread {
    private Point pos;
    private Point dir;
    private Rectangle boundary;
    private Random random = new Random();
    private MyPanel originator;

    PointMover(Rectangle boundary, boolean leftX, MyPanel originator) {
        this.boundary = boundary;
        this.originator = originator;
        this.pos = new Point(
                (leftX ? 0 : boundary.width - 1),
                random.nextInt(boundary.height)
        );
        this.dir = new Point((leftX ? 1 : -1), 0);
    }

    @Override
    public void run() {
        while (boundary.contains(pos)) {
            pos.translate(dir.x, dir.y);
            if (originator != null) {
                originator.repaint();
            }

            try {
                this.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        if (originator != null) {
            originator.setPoint(getNextPoint());
        }
    }

    public Point getPos() {
        return pos;
    }

    public PointMover getNextPoint() {
        return new PointMover(boundary, pos.x < 0, originator);
    }

    public void drawPoint(Graphics area, Color color) {
        area.setColor(color);
        area.drawRect(
                pos.x, pos.y,
                1, 1
        );
    }
}