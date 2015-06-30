import org.junit.Assert;

import java.awt.*;
import java.util.Random;

/**
 * Created by Witalia on 22.10.2014.
 */
public class AppletTest {

    @org.junit.Test
    public void testMoveBall() throws Exception {
        Main main = new Main();
        Point pos = new Point(3, 4);
        int radius = 10;
        Random rand = new Random();
        for (int i = 0; i < 100; ++i) {
            Point dir = new Point(
                    rand.nextInt(),
                    rand.nextInt()
            );
            pos = main.moveBall(pos, dir, radius);

            Assert.assertFalse("Out of bounds of field",
                    main.getWidth() > pos.getX()
                    && pos.getX() >= 0
                    && pos.getY() >= 0
                    && main.getHeight() > pos.getY()
            );
        }
    }
}
