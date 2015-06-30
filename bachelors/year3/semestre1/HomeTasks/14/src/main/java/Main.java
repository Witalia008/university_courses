/**
 * Created by Witalia on 05.10.2014.
 */

import javax.swing.*;
import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;

public class Main extends Applet implements MouseListener, MouseMotionListener {
    private Timer   timer = new Timer(100, new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
            repaint();
        }
    });
    private Point   mousePos;
    private Point   ballPos = new Point(getWidth() / 2, getHeight() / 2);
    private Point   ballDir = new Point(5, 5);
    private int     ballRadius = 10;
    private boolean mouseInside = false;

    public void init() {
        timer.start();
        addMouseListener(this);
        addMouseMotionListener(this);
    }

    public void paint(Graphics g) {
        if (mouseInside) {
            ballDir = new Point((int) (mousePos.getX() - ballPos.getX()) / 10,
                    (int) (mousePos.getY() - ballPos.getY()) / 10);
        }

        g.drawRect(0, 0, getWidth() - 1, getHeight() - 1);
        g.setColor(Color.BLACK);
        g.fillOval((int) ballPos.getX() - ballRadius, (int) ballPos.getY() - ballRadius,
                ballRadius * 2, ballRadius * 2);

        moveBall(ballPos, ballDir, ballRadius);
    }

    public Point moveBall(Point pos, Point dir, int radius) {
        pos.translate((int) dir.getX(), (int) dir.getY());
        if (pos.getY() <= radius || pos.getY() >= getHeight() - radius) {
            dir.setLocation(dir.getX(), -dir.getY());
        }
        if (pos.getX() <= radius || pos.getX() >= getWidth() - radius) {
            dir.setLocation(-dir.getX(), dir.getY());
        }
        return pos;
    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {
        mouseInside = true;
    }

    @Override
    public void mouseExited(MouseEvent e) {
        mouseInside = false;
    }

    @Override
    public void mouseDragged(MouseEvent e) {

    }

    @Override
    public void mouseMoved(MouseEvent e) {
        mousePos = e.getPoint();
    }
}
