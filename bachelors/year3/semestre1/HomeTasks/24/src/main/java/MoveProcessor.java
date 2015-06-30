import java.awt.*;
import java.util.Random;

/**
 * Created by Witalia on 23.10.2014.
 */
class MoveProcessor extends Thread {
    private Rectangle allowedRect;
    private Point position;
    private Point direction;
    private Random random;
    private Component component;
    private boolean needToRun;

    public Point getPosition() {
        return position;
    }

    public Point getDirection() {
        return direction;
    }

    MoveProcessor(Rectangle allowedRect, Component component) {
        this.allowedRect = allowedRect;
        this.component = component;
        random = new Random();
        position = new Point(
                random.nextInt(allowedRect.width),
                random.nextInt(allowedRect.height)
        );
        direction = updateDirection(null);
        needToRun = true;
    }

    @Override
    public void run() {
        while (needToRun) {
            position = updatePosition(position, direction);
            if (component != null) {
                component.setBounds(position.x, position.y,
                        component.getWidth(), component.getHeight());
            }
            if (random.nextInt(20) == 0) {
                direction = updateDirection(direction);
            }
            try {
                this.sleep(100);
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            }
        }
    }

    public Point updatePosition(Point position, Point direction) {
        position.translate(direction.x, direction.y);
        if (allowedRect.contains(position) == false) {
            position.setLocation(
                    Math.min(Math.max(allowedRect.x, position.x),
                            allowedRect.width + allowedRect.x - 1),
                    Math.min(Math.max(allowedRect.y, position.y),
                            allowedRect.height + allowedRect.y - 1)
            );
            direction = updateDirection(direction);
        }
        return position;
    }

    public Point updateDirection(Point direction) {
        if (direction == null) {
            direction = new Point();
        }
        direction.setLocation(
                random.nextInt(40) - 20,
                random.nextInt(40) - 20
        );
        return direction;
    }

    public void end() {
        needToRun = false;
    }
}