import org.junit.Assert;
import org.junit.Test;
import sample.FileUtils;

import java.io.File;
import java.io.PrintWriter;

/**
 * Created by Witalia on 29.11.14.
 */
public class WordCountTester {
    @Test
    public void testCountWords() throws Exception {
        File[] files = new File[] {
                new File("f1"),
                new File("f2")
        };
        new PrintWriter(files[0]).println("The quick brown fox jumps over the lazy dog!");
        new PrintWriter(files[1]).println("Word, again - no word, huh?");
        Assert.assertTrue(FileUtils.getWordsCount(files) == 14);
        for (File file : files) {
            if (file.exists()) {
                file.delete();
            }
        }
    }
}
