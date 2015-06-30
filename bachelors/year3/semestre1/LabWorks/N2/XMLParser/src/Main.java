/**
 * Created by witalia on 9/20/14.
 */

import javax.xml.XMLConstants;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import java.io.*;

public class Main {
    public static void main(String [] args) {
        System.out.println("Hello, world!");
        try {
            System.out.println("Validate: "
                    + validateAgainstXSD(new FileInputStream("src/gems.xml"),
                    new FileInputStream("src/gems.xsd")));
            System.out.println("Convert to HTML: "
                    + convertToHTML(new FileInputStream("src/gems.xml"),
                    new FileInputStream("src/gems.xsl"), "src/gems.html"));
        } catch (FileNotFoundException ex) {
            System.out.println("File not found!");
        }
        try {
            System.out.print("DOM  Parser: ");
            DOMParser.parse(new FileInputStream("src/gems.xml"));
            System.out.print("SAX  Parser: ");
            SAXParserMy.parse(new FileInputStream("src/gems.xml"));
            System.out.print("StAX Parser: ");
            StAXParser.parse(new FileInputStream("src/gems.xml"));
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public static boolean validateAgainstXSD(InputStream xml, InputStream xsd) {
        try
        {
            SchemaFactory factory = SchemaFactory.newInstance(
                    XMLConstants.W3C_XML_SCHEMA_NS_URI);
            Schema schema = factory.newSchema(new StreamSource(xsd));
            Validator validator = schema.newValidator();
            validator.validate(new StreamSource(xml));
            return true;
        }
        catch(Exception ex)
        {
            System.out.println("Error: " + ex.getMessage());
            return false;
        }
    }

    public static boolean convertToHTML(InputStream xml, InputStream xsl,
                                        String htmlFileName) {
        try {
            TransformerFactory tFactory = TransformerFactory.newInstance();

            Source xmlDoc = new StreamSource(xml);
            Source xslDoc = new StreamSource(xsl);

            OutputStream htmlFile = new FileOutputStream(htmlFileName);

            Transformer transformer = tFactory.newTransformer(xslDoc);
            transformer.transform(xmlDoc, new StreamResult(htmlFile));
            return true;
        } catch (Exception ex) {
            ex.printStackTrace();
            return false;
        }
    }
}
