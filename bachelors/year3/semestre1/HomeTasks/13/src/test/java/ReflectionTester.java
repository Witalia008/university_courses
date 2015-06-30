import org.junit.Assert;

/**
 * Created by Witalia on 22.10.2014.
 */
public class ReflectionTester {
    @org.junit.Test
    public void testClassLoading() throws Exception {
        Loader loader = new Loader(
                ClassLoader.getSystemClassLoader(),
                "target\\classes\\"
        );
        Class PrinterMy = loader.findClass("Printer");
        Object printer = PrinterMy.newInstance();
        Assert.assertEquals("This is not my class :(",
                "Hello, world!", printer.toString());
    }
}
