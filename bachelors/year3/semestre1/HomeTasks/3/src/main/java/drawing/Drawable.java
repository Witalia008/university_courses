package drawing;

import java.awt.*;
import java.io.Serializable;

/**
 * Created by Witalia on 07.12.2014.
 */
public abstract class Drawable implements Serializable {
    protected Color bgColor;
    protected Color fgColor;
    protected Point lu;
    protected Point rd;

    public void setBgColor(Color bgColor) {
        this.bgColor = bgColor;
    }

    public void setFgColor(Color fgColor) {
        this.fgColor = fgColor;
    }

    public void setLu(Point lu) {
        this.lu = lu;
    }

    public void setRd(Point rd) {
        this.rd = rd;
    }

    abstract public void draw(Graphics g);
}
