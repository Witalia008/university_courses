
package ents;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.ErrorHandler;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import javax.xml.bind.annotation.adapters.NormalizedStringAdapter;
import javax.xml.bind.annotation.adapters.XmlJavaTypeAdapter;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;


/**
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "category"
})
@XmlRootElement(name = "stock")
public class Stock {

    @XmlAttribute(name = "xmlns")
    @XmlJavaTypeAdapter(NormalizedStringAdapter.class)
    protected String xmlns;
    @XmlElement(required = true)
    protected List<Category> category;
    protected List<Product> product;
    /**
     * Gets the value of the xmlns property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getXmlns() {
        if (xmlns == null) {
            return "";
        } else {
            return xmlns;
        }
    }

    /**
     * Sets the value of the xmlns property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setXmlns(String value) {
        this.xmlns = value;
    }

    /**
     * Gets the value of the category property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the category property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getCategory().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link Category }
     * 
     * 
     */
    public List<Category> getCategory() {
        if (category == null) {
            category = new ArrayList<Category>();
        }
        return this.category;
    }

    public void saveToFile(String fileName) {
        DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
        try {
            DocumentBuilder db = dbf.newDocumentBuilder();
            Document doc = db.newDocument();
            Element root = doc.createElement("stock");
            doc.appendChild(root);
            for (Category c : category) {
                Element cat = doc.createElement("category");
                cat.setAttribute("id", c.getId());
                cat.setAttribute("name", c.getName());
                root.appendChild(cat);
                for (Product p : c.product) {
                    Element prod = doc.createElement("product");
                    prod.setAttribute("id", p.getId());
                    prod.setAttribute("name", p.getName());
                    prod.setAttribute("count", p.getCount());
                    prod.setAttribute("price", p.getPrice());
                    prod.setAttribute("fat", p.getFat());
                    cat.appendChild(prod);
                }
            }
            Source domSource = new DOMSource(doc);
            Result fileRes = new StreamResult(new File(fileName));
            TransformerFactory factory = TransformerFactory.newInstance();
            Transformer transformer = factory.newTransformer();
            transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
            transformer.transform(domSource, fileRes);
        } catch (ParserConfigurationException | TransformerException e) {
            e.printStackTrace();
        }
    }

    class SimpleErrorHandler implements ErrorHandler {

        @Override
        public void warning(SAXParseException exception) throws SAXException {
            System.out.println("Line " + exception.getLineNumber() + ":");
            System.out.println(exception.getMessage());
        }

        @Override
        public void error(SAXParseException exception) throws SAXException {
            System.out.println("Line " + exception.getLineNumber() + ":");
            System.out.println(exception.getMessage());
        }

        @Override
        public void fatalError(SAXParseException exception) throws SAXException {
            System.out.println("Line " + exception.getLineNumber() + ":");
            System.out.println(exception.getMessage());
        }
    }

    public Stock() {
        category = new ArrayList<>();
        product = new ArrayList<>();
    }

    public void loadFromFile(String fileName) {
        DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
        dbf.setValidating(true);
        try {
            DocumentBuilder db = dbf.newDocumentBuilder();
            db.setErrorHandler(new SimpleErrorHandler());
            Document doc = db.parse(new File(fileName));
            Element root = doc.getDocumentElement();
            if (root.getTagName().equals("stock")) {
                NodeList categories = root.getElementsByTagName("category");
                for (int i = 0; i < categories.getLength(); i++) {
                    Element cat = (Element) categories.item(i);
                    String catID = cat.getAttribute("id");
                    String catName = cat.getAttribute("name");
                    Category c = new Category(catID, catName);
                    category.add(c);

                    System.out.println(catID + " " + catName + ":");

                    NodeList products = cat.getElementsByTagName("product");
                    for (int j = 0; j < products.getLength(); j++) {
                        Element prod = (Element) products.item(j);
                        String prodName = prod.getAttribute("name");
                        Product p = new Product(
                                prod.getAttribute("count"),
                                prod.getAttribute("fat"),
                                prod.getAttribute("id"),
                                prod.getAttribute("name"),
                                prod.getAttribute("price")
                        );
                        c.product.add(p);
                        product.add(p);
                        System.out.println("       "+ prodName);
                    }
                }
            }
        } catch (ParserConfigurationException | SAXException | IOException e) {
            e.printStackTrace();
        }
    }

    public void addCategory(int id, String name) {
        try {
            getCategory(id);
        } catch (Exception ex) {
            category.add(new Category("" + id, name));
        }
    }

    public Category getCategory(int id) throws Exception {
        for (Category c : category) {
            if (c.getId().equals(""+id)) {
                return c;
            }
        }
        throw new Exception("No such category id");
    }

    public void deleteCategory(int id) throws Exception {
        Category c = getCategory(id);
        category.remove(c);
    }

    public void addProduct(
            int id, String name, double price,
            int count, int fat, int catID) throws Exception {
        try {
            getProduct(id);
        } catch (Exception ex) {
            Category c = getCategory(catID);
            Product p = new Product("" + count, "" + fat, "" + id, name, "" + price);
            c.product.add(p);
            product.add(p);
        }
    }

    public Product getProduct(int id) throws Exception {
        for (Product p : product) {
            if (p.getId().equals(""+id)) {
                return p;
            }
        }
        throw new Exception("No product with such id");
    }

    public void deleteProduct(int id) throws Exception {
        Product p = getProduct(id);
        product.remove(p);
        for (Category c : category) {
            c.product.remove(p);
        }
    }

    public void changeCategory(int id, Category c) throws Exception {
        Category cx = getCategory(id);
        if (c.getName() != null) {
            cx.setName(c.getName());
        }
    }

    public void changeProduct(int id, Product p) throws Exception {
        Product px = getProduct(id);
        if (p.getName() != null) {
            px.setName(p.getName());
        }
        if (p.getCount() != null) {
            px.setCount(p.getCount());
        }
        if (p.getFat() != null) {
            px.setFat(p.getFat());
        }
        if (p.getPrice() != null) {
            px.setPrice(p.getPrice());
        }
    }
}
