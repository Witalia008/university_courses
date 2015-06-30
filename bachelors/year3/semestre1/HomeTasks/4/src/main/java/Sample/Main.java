package Sample;
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

    public static String convertToHTML(InputStream xml, InputStream xsl) {
        try {
            TransformerFactory tFactory = TransformerFactory.newInstance();

            Source xmlDoc = new StreamSource(xml);
            Source xslDoc = new StreamSource(xsl);

            ByteArrayOutputStream out = new ByteArrayOutputStream();
            Transformer transformer = tFactory.newTransformer(xslDoc);
            transformer.transform(xmlDoc, new StreamResult(out));
            return new String(out.toByteArray());
        } catch (Exception ex) {
            ex.printStackTrace();
            return "Error";
        }
    }
}
