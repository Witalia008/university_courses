package drawing;

import java.awt.*;

/**
 * Created by Witalia on 07.12.2014.
 */
public class DrawableFactory {
    public static Drawable getDrawable(String name) {
        Drawable res = null;
        switch (name) {
            case "ellipse":
                res = new Ellipse();
                break;
            case "line":
                res = new Line();
                break;
            case "rect":
                res = new Rectangle();
                break;
            default:
                break;
        }
        return res;
    }
}

class Ellipse extends Drawable {
    @Override
    public void draw(Graphics g) {
        g.setColor(bgColor);
        g.fillOval(lu.x, lu.y, rd.x - lu.x, rd.y - lu.y);
        g.setColor(fgColor);
        g.drawOval(lu.x, lu.y, rd.x - lu.x, rd.y - lu.y);
    }
}

class Rectangle extends Drawable {
    @Override
    public void draw(Graphics g) {
        g.setColor(bgColor);
        g.fillRect(lu.x, lu.y, rd.x - lu.x, rd.y - lu.y);
        g.setColor(fgColor);
        g.drawRect(lu.x, lu.y, rd.x - lu.x, rd.y - lu.y);
    }
}

class Line extends Drawable {
    @Override
    public void draw(Graphics g) {
        g.setColor(fgColor);
        g.drawLine(lu.x, lu.y, rd.x, rd.y);
    }
}

