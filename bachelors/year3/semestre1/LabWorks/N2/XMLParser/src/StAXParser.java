/**
 * Created by witalia on 9/23/14.
 */

import generated.*;
import org.xml.sax.SAXException;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamReader;
import java.io.InputStream;
import java.math.BigInteger;

public class StAXParser {
    public static void parse(InputStream xml) throws Exception {
        StAXHandler handler = new StAXHandler();
        XMLInputFactory factory = XMLInputFactory.newInstance();
        XMLStreamReader reader = factory.createXMLStreamReader(xml);

        while (reader.hasNext()) {
            int event = reader.next();

            switch (event) {
                case XMLStreamConstants.START_ELEMENT:
                    handler.startElement(reader);
                    break;
                case XMLStreamConstants.CHARACTERS:
                    handler.characters(reader);
                    break;
                case XMLStreamConstants.END_ELEMENT:
                    handler.endElement(reader);
                    break;
                default:
                    break;
            }
        }

        System.out.println(handler.getGems());
    }
}

class StAXHandler {
    private Gems            gems = new Gems();
    private GemType         curGem = null;
    private VpType          appearance = null;
    private VpEngravingType engraving = null;
    private String          content = null;

    public void startElement(XMLStreamReader reader)
            throws SAXException {
        switch (reader.getLocalName()) {
            case "gems":
                gems = new Gems();
                break;
            case "gem":
                curGem = new GemType();
                curGem.setId(reader.getAttributeValue(0));
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

    public void endElement(XMLStreamReader reader) throws SAXException {
        switch (reader.getLocalName()) {
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

    public void characters(XMLStreamReader reader)
            throws SAXException {
        content = reader.getText().trim();
    }


    public Gems getGems() {
        return gems;
    }
}