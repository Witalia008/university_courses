package beans;

import javax.persistence.*;
import java.io.Serializable;

/**
 * Created by Witalia on 04.04.2015.
 */
@Entity
@Table(name = "cars")
public class Car implements Serializable {

    @Id @GeneratedValue
    @Column(name = "ID")
    private int id;

    @Column(name = "_NAME")
    private String name;

    @Column(name = "SEATS")
    private int numOfSeats;

    @Column(name = "PRICE")
    private double price;

    @OneToOne(fetch = FetchType.LAZY, mappedBy = "car")
    private Order order;


    public Car(String name, int numOfSeats, double price) {
        this.name = name;
        this.numOfSeats = numOfSeats;
        this.price = price;
    }

    public Car() {}

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }

    public int getNumOfSeats() {
        return numOfSeats;
    }
    public void setNumOfSeats(int numOfSeats) {
        this.numOfSeats = numOfSeats;
    }

    public double getPrice() {
        return price;
    }
    public void setPrice(double price) {
        this.price = price;
    }

    public Order getOrder() {
        return order;
    }
    public void setOrder(Order order) {
        this.order = order;
    }
}
