import org.junit.Assert;

import java.awt.*;

/**
 * Created by Witalia on 23.10.2014.
 */
public class TestPoints {
    @org.junit.Test
    public void testPointMovement() throws Exception {
        Rectangle boundary = new Rectangle(0, 0, 30, 30);
        PointMover mover = new PointMover(
                boundary,
                true,
                null
        );
        for (int i = 0; i < 10; ++i) {
            Assert.assertFalse(!(i % 2 == 0
                    ? (mover.getPos().x == 0)
                    : (mover.getPos().x == boundary.width - 1)
            ));
            mover.run();
            mover = mover.getNextPoint();
        }
    }
}
