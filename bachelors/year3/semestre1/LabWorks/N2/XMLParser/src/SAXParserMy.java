/**
 * Created by witalia on 9/23/14.
 */

import generated.*;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.Attributes;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.InputStream;
import java.math.BigInteger;

public class SAXParserMy {
    public static void parse(InputStream xml) throws Exception {
        SAXParserFactory parserFactory = SAXParserFactory.newInstance();
        SAXParser parser = parserFactory.newSAXParser();
        SAXHandler handler = new SAXHandler();

        parser.parse(xml, handler);

        System.out.println(handler.getGems());
    }
}

class SAXHandler extends DefaultHandler {
    private Gems            gems = new Gems();
    private GemType         curGem = null;
    private VpType          appearance = null;
    private VpEngravingType engraving = null;
    private String          content = null;

    @Override
    public void startElement(String uri, String localName,
                             String qName, Attributes attributes)
                             throws SAXException {
        switch (qName) {
            case "gem":
                curGem = new GemType();
                curGem.setId(attributes.getValue("id"));
                break;
            case "visualParameters":
                appearance = new VpType();
                break;
            case "engraving":
                engraving = new VpEngravingType();
                break;
            default:
                break;
        }
    }

    @Override
    public void endElement(String uri, String localName,
                           String qName) throws SAXException {
        switch (qName) {
            case "gem":
                gems.getGem().add(curGem);
                break;
            case "name":
                curGem.setName(content);
                break;
            case "preciousness":
                curGem.setPreciousness(
                        PreciousType.fromValue(content)
                );
                break;
            case "origin":
                curGem.setOrigin(content);
                break;
            case "value":
                curGem.setValue(
                        new BigInteger(content)
                );
                break;
            case "visualParameters":
                curGem.setVisualParameters(appearance);
                break;
            case "color":
                appearance.setColor(content);
                break;
            case "transparency":
                appearance.setTransparency(content);
                break;
            case "engraving":
                appearance.setEngraving(engraving);
                break;
            case "type":
                engraving.setType(content);
                break;
            case "numberOfSides":
                engraving.setNumberOfSides(
                        Integer.parseInt(content)
                );
                break;
            default:
                break;
        }
    }

    @Override
    public void characters(char[] ch, int start, int length)
            throws SAXException {
        content = String.copyValueOf(ch, start, length).trim();
    }

    public Gems getGems() {
        return gems;
    }
}
