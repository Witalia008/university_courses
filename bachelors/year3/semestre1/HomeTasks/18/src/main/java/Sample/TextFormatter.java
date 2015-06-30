package Sample;

import java.io.*;
import java.util.Arrays;

/**
 * Created by Witalia on 01.11.2014.
 */
public class TextFormatter {
    private int paragraphTabSpaces;
    private int sheetCharsWidth;

    public TextFormatter(int paragraphTabSpaces, int sheetCharsWidth) {
        this.paragraphTabSpaces = paragraphTabSpaces;
        this.sheetCharsWidth = sheetCharsWidth;
    }

    public void format(BufferedReader in, PrintWriter out) {
        String inputLine;
        try {
            while ((inputLine = in.readLine()) != null) {
                out.println(formatParagraph(inputLine));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String formatParagraph(String paragraph) {
        if (paragraph.isEmpty()) {
            return paragraph;
        }
        StringBuffer result = new StringBuffer(getString(3, ' '));
        for (int i = 1; !paragraph.isEmpty(); i = 0) {
            paragraph = paragraph.trim();
            int currentLength = sheetCharsWidth - i * paragraphTabSpaces;
            String currentLine = getNextLine(paragraph, currentLength);
            paragraph = paragraph.substring(currentLine.length());
            result.append(formatLine(currentLine, currentLength) + "\n");
        }
        return result.toString();
    }

    public String getString(int length, char ch) {
        if (length == 0) {
            return "";
        }
        char[] array = new char[length];
        Arrays.fill(array, ch);
        return new String(array);
    }

    public String formatLine(String currentLine, int desiredLength) {
        String[] parts = currentLine.split("\\s+");
        if (parts.length <= 1) {
            parts = currentLine.split("");
        }

        StringBuffer result = new StringBuffer();

        int length = Math.max(desiredLength, currentLine.length());
        for (String cur : parts) {
            length -= cur.length();
        }

        int numberOfBigger = length % (parts.length - 1);
        int numberPerGap = length / (parts.length - 1);

        for (int i = 0; i < parts.length; i++) {
            if (i > 0) {
                result.append(getString(
                        numberPerGap + (i <= numberOfBigger ? 1 : 0), ' '
                        ));
            }
            result.append(parts[i]);
        }

        return result.toString();
    }

    public String getNextLine(String paragraph, int width) {
        if (width >= paragraph.length()
                || paragraph.indexOf(' ') == -1) {
            return paragraph;
        }
        if (paragraph.indexOf(' ') >= width) {
            return paragraph.substring(0, paragraph.indexOf(' '));
        }
        while (width > 0 && Character.isAlphabetic(paragraph.charAt(width))
                         && !Character.isWhitespace(paragraph.charAt(width - 1))) {
            --width;
        }
        return paragraph.substring(0, width);
    }
}
