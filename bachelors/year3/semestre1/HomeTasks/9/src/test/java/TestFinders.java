import org.junit.Assert;
import org.junit.Test;
import tags.ArrUtil;
import tags.LocalMaxFinder;
import tags.LocalMinFinder;

/**
 * Created by Witalia on 23.11.2014.
 */
public class TestFinders {
    @Test
    public void testArrayConversion() throws Exception {
        Integer[] a = ArrUtil.toIntArr(new String[]{"-1", "0", "1"});
        for (int i = -1; i <= 1; ++i) {
            Assert.assertTrue(a[i + 1] == i);
        }
    }

    @Test
    public void testLocalMin() throws Exception {
        LocalMinFinder minFinder = new LocalMinFinder();
        minFinder.setArray(new Integer[]{1, 2, -1, -2, 3});
        Assert.assertArrayEquals(minFinder.getMins(), new Integer[]{1, -2});
    }

    @Test
    public void testLocalMax() throws Exception {
        LocalMaxFinder maxFinder = new LocalMaxFinder();
        maxFinder.setArray(new Integer[]{1, 2, -1, -2, 3});
        Assert.assertArrayEquals(maxFinder.getMaxs(), new Integer[]{2, 3});
    }
}
