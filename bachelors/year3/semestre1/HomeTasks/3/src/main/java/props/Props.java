package props;

import javafx.util.Pair;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Witalia on 08.12.2014.
 */
public class Props {
    private List<Pair<String, String>> props;
    public Props(InputStream is) {
        SAXParserFactory parserFactory = SAXParserFactory.newInstance();
        try {
            SAXParser parser = parserFactory.newSAXParser();
            Handler h = new Handler();
            parser.parse(is, h);
            props = h.getPropertiesList();
        } catch (IOException | ParserConfigurationException | SAXException e) {
            e.printStackTrace();
        }
    }

    public boolean contains(String key, String value) {
        for (Pair x : props) {
            if (x.getKey().equals(key) && x.getValue().equals(value)) {
                return true;
            }
        }
        return false;
    }

    public String getValue(String key) {
        for (Pair x : props) {
            if (x.getKey().equals(key)) {
                return ((String) x.getValue());
            }
        }
        return null;
    }
}

class Handler extends DefaultHandler {
    private String content;
    private List<Pair<String, String>> propertiesList
             = new ArrayList<>();

    public List<Pair<String, String>> getPropertiesList() {
        return propertiesList;
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException {
        propertiesList.add(new Pair<>(qName, content));
    }

    @Override
    public void characters(char[] ch, int start, int length) throws SAXException {
        content = String.copyValueOf(ch, start, length).trim();
    }
}