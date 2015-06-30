import org.junit.Assert;
import org.junit.Test;

import java.awt.*;

/**
 * Created by Witalia on 23.10.2014.
 */
public class TestFlyingGIFs {
    @org.junit.Test
    public void testMovingProcessing() throws Exception {
        Rectangle rect = new Rectangle(20, 47, 139, 458);
        MoveProcessor mover = new MoveProcessor(rect, null);
        for (int i = 0; i < 100; ++i) {
            mover.updatePosition(mover.getPosition(), mover.getDirection());
            Assert.assertFalse("Out of bounds\n" + rect + "\n" + mover.getPosition(),
                    !rect.contains(mover.getPosition()));
            Assert.assertFalse("Wrong direction format",
                    !new Rectangle(-20, -20, 40, 40).contains(mover.getDirection()));
        }
    }

    @Test
    public void testSelectingGIFs() throws Exception {
        Main main = new Main();
        main.createAndShowGui();
        Assert.assertArrayEquals("Not all GIFs loaded",
                main.getComboBoxItems(),
                main.getImageFiles());
    }
}
