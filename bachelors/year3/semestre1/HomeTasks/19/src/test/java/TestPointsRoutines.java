import dbtools.Database;
import javafx.util.Pair;
import org.junit.Assert;
import org.junit.Test;
import tags.MaximumPoints;

import java.util.List;

/**
 * Created by Witalia on 23.11.2014.
 */
public class TestPointsRoutines {
    @Test
    public void testDatabase() throws Exception {
        Assert.assertNotNull(Database.getConnection());

        Pair p = Database.get();
        Assert.assertNotNull(p);
    }

    @Test
    public void testDivision() throws Exception {
        MaximumPoints mp = new MaximumPoints();
        mp.setPtX(1);
        mp.setPtY(2);
        List l = mp.getDivision(Database.get(),
                new Integer[]{2, 4, 8, 10, 12});
        Assert.assertNotNull(l);
    }
}
