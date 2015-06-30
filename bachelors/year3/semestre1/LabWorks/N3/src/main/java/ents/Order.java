package ents;

import org.apache.log4j.Logger;

/**
 * Class for storing user's orders.
 * Created by Witalia on 22.11.2014.
 */
public class Order {
    private static Logger logger = Logger.getLogger(Order.class);

    protected int id;
    protected int productId;
    protected int userId;
    protected int amount;
    protected int total;


    /** Constructors */
    public Order() {}

    public Order(int productId, int userId, int amount, int total) {
        this.productId = productId;
        this.userId = userId;
        this.amount = amount;
        this.total = total;
    }

    /** Setters */
    public void setId(int id) {
        this.id = id;
    }

    public void setProductId(int productId) {
        this.productId = productId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    public void setTotal(int total) {
        this.total = total;
    }

    /** Getters */
    public int getId() {
        return id;
    }

    public int getProductId() {
        return productId;
    }

    public int getUserId() {
        return userId;
    }

    public int getAmount() {
        return amount;
    }

    public int getTotal() {
        return total;
    }
}
