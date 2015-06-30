import org.junit.Assert;
import org.junit.Test;

/**
 * Created by Witalia on 29.10.2014.
 */
public class ReaderTester {
    @Test
    public void testDatabaseUsage() throws Exception {
        Database database = new Database();
        Assert.assertFalse(database.getConnection() == null);
    }

    @Test
    public void testReporter() throws Exception {
        Report report = new Report();
        report.print(new Database());
        Assert.assertFalse(report.getJasperPrint() == null);
        Assert.assertFalse(report.getJasperReport() == null);
    }

    @Test
    public void testReading() throws Exception {
        Assert.assertEquals(FileReader.readFile("http://e-olimp.com.ua/robots.txt"), null);
        Assert.assertFalse(FileReader.readFile(
                "http://e-olimp.com.ua/no_such_file.txt") != null);
    }
}
