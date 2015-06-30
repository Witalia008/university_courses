import Sample.TextFormatter;
import org.junit.Assert;
import org.junit.Test;

/**
 * Created by Witalia on 01.11.2014.
 */
public class TestFormatter {
    String input = "aaa a aa aaaaaaaaaaaa a aaaa aaaaaaaa a aaaa a aaaaaa aaaaaa"
            + " a a aaaaa aaaaaaaaaaaaaa a aaaaaaaaaaa a aaaaaaaaaaaaaaaaaaaaaa";
    TextFormatter formatter = new TextFormatter(3, 80);

    @Test
    public void testFormattingParagraph() throws Exception {
        String output = formatter.formatParagraph(input);
        while (!output.isEmpty()) {
            Assert.assertTrue(80 == output.indexOf('\n') ||
                    output.substring(0, 80).indexOf(' ') == -1);
            output = output.substring(output.indexOf('\n') + 1);
        }
    }

    @Test
    public void testGetNextLine() throws Exception {
        Assert.assertEquals(71, formatter.getNextLine(input, 80).length());
        Assert.assertEquals(3, formatter.getNextLine(input, 3).length());
        Assert.assertEquals(input.length(),
                formatter.getNextLine(input, input.length()).length());
        Assert.assertEquals(input.lastIndexOf(' ') + 1,
                formatter.getNextLine(input, input.length() - 1).length());
        Assert.assertEquals(3,
                formatter.getNextLine(input.substring(0, 3), 2).length());
    }

    @Test
    public void testFormatLine() throws Exception {
        String oneLine = formatter.getNextLine(input, 80).trim();
        String output = formatter.formatLine(oneLine, 90);
        Assert.assertEquals(90, output.length());
        output = formatter.formatLine(oneLine, 60);
        Assert.assertEquals(oneLine, output);
    }
}
