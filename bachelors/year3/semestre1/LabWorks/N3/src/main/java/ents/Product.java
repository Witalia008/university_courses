package ents;

import org.apache.log4j.Logger;

/**
 * Class for storing product available for users.
 * Created by Witalia on 22.11.2014.
 */
public class Product {
    private static Logger logger = Logger.getLogger(Product.class);

    protected int id;
    protected String type;
    protected String name;
    protected int price;
    protected String description;


    /** Constructors */
    public Product() {}
    public Product(String type, String name, int price, String description) {
        this.type = type;
        this.name = name;
        this.price = price;
        this.description = description;
    }

    /** Setters */
    public void setId(int id) {
        this.id = id;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    /** Getters */
    public int getId() {

        return id;
    }

    public String getType() {
        return type;
    }

    public String getName() {
        return name;
    }

    public int getPrice() {
        return price;
    }

    public String getDescription() {
        return description;
    }
}
