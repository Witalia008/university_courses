import Sample.Main;
import org.junit.Assert;
import org.junit.Test;

import java.io.File;
import java.io.FileInputStream;

/**
 * Created by Witalia on 04.11.2014.
 */
public class TestDynamicWebPage {
    private File xml = new File("target\\classes\\data\\gems.xml");
    private File xsd = new File("target\\classes\\data\\gems.xsd");
    private File xsl = new File("target\\classes\\data\\gems.xsl");
    @Test
    public void testDataFiles() throws Exception {
        Assert.assertTrue(xml.exists());
        Assert.assertTrue(xsl.exists());
        Assert.assertTrue(xsd.exists());
    }

    @Test
    public void testTransformation() throws Exception {
        Assert.assertTrue(Main.validateAgainstXSD(
                new FileInputStream(xml), new FileInputStream(xsd)));
        Assert.assertFalse(Main.convertToHTML(
                new FileInputStream(xml), new FileInputStream(xsl)).equals("Error"));
    }
}
