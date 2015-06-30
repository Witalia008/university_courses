/**
 * Created by witalia on 9/22/14.
 */

import generated.*;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.FileInputStream;
import java.io.InputStream;
import java.math.BigInteger;

public class DOMParser {
    public static void parse(InputStream xml) throws Exception {
        // Get the DOM Builder Factory
        DocumentBuilderFactory factory =
                DocumentBuilderFactory.newInstance();

        // Get the DOM Builder
        DocumentBuilder builder = factory.newDocumentBuilder();

        // Load and Parse the XML Document
        // document contains the complete XML as a Tree.
        Document document = builder.parse(xml);

        // Iterating through the nodes and extracting data
        NodeList nodeList = document.getDocumentElement().getChildNodes();

        Gems gems = parseAllGems(nodeList);

        System.out.println(gems);
    }

    private static Gems parseAllGems(NodeList nodeList) {
        Gems gems = new Gems();
        for (int i = 0; i < nodeList.getLength(); ++i) {
            // We have encountered 'gem' tag.
            Node gemNode = nodeList.item(i);
            if (gemNode instanceof Element) {
                gems.getGem().add(parseSingleGem(gemNode));
            }
        }
        return gems;
    }

    private static GemType parseSingleGem(Node gemNode) {
        GemType curGem = new GemType();
        NodeList gemChildNodes = gemNode.getChildNodes();

        curGem.setId(gemNode.getAttributes()
                .getNamedItem("id").getNodeValue());

        // Iterate child nodes of gem
        for (int j = 0; j < gemChildNodes.getLength(); ++j) {
            Node gemChildNode = gemChildNodes.item(j);

            if (gemChildNode instanceof Element) {
                String nodeName = gemChildNode.getNodeName();
                String content = gemChildNode.getLastChild()
                        .getTextContent().trim();

                switch (nodeName) {
                    case "name":
                        curGem.setName(content);
                        break;
                    case "preciousness":
                        curGem.setPreciousness(PreciousType.fromValue(content));
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
                        curGem.setVisualParameters(
                                parseVisualParameters(gemChildNode)
                        );
                        break;
                    default:
                        break;
                }
            }
        }
        return curGem;
    }

    private static VpType parseVisualParameters(Node vpNode) {
        VpType vp = new VpType();
        NodeList vpChildList = vpNode.getChildNodes();

        for (int i = 0; i < vpChildList.getLength(); ++i) {
            Node vpChildNode = vpChildList.item(i);

            if (vpChildNode instanceof Element) {
                String nodeName = vpChildNode.getNodeName();
                String content = vpChildNode.getLastChild()
                        .getTextContent().trim();

                switch (nodeName) {
                    case "color":
                        vp.setColor(content);
                        break;
                    case "transparency":
                        vp.setTransparency(content);
                        break;
                    case "engraving":
                        vp.setEngraving(
                                parseEngraving(vpChildNode)
                        );
                        break;
                    default:
                        break;
                }
            }
        }
        return vp;
    }

    private static VpEngravingType parseEngraving(Node engravingNode) {
        VpEngravingType engraving = new VpEngravingType();
        NodeList engravingChildList = engravingNode.getChildNodes();

        for (int i = 0; i < engravingChildList.getLength(); ++i) {
            Node engravingChild = engravingChildList.item(i);

            if (engravingChild instanceof Element) {
                String nodeName = engravingChild.getNodeName();
                String content = engravingChild.getLastChild().
                        getTextContent().trim();

                switch (nodeName) {
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
        }

        return engraving;
    }
}
