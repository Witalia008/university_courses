package beans;

import javax.persistence.*;
import java.io.Serializable;

/**
 * Created by Witalia on 04.04.2015.
 */
@Entity
@Table(name = "bills")
public class Bill implements Serializable {

    @Id @GeneratedValue
    @Column(name = "ID")
    private int id;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "ORDER_ID")
    private Order order;

    @Column(name = "AMOUNT")
    private int amount;

    @Column(name = "COMMENT")
    private String comment;

    public Bill() {    }

    public Bill(Order order, int amount, String comment) {

        this.order = order;
        this.amount = amount;
        this.comment = comment;
    }

    public int getId() {
        return id;
    }

    public Order getOrder() {
        return order;
    }
    public void setOrder(Order order) {
        this.order = order;
    }

    public int getAmount() {
        return amount;
    }
    public void setAmount(int amount) {
        this.amount = amount;
    }

    public String getComment() {
        return comment;
    }
    public void setComment(String comment) {
        this.comment = comment;
    }
}
