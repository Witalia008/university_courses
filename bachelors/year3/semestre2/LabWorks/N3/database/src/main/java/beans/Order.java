package beans;

import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by Witalia on 04.04.2015.
 */
@Entity
@Table(name = "orders")
public class Order implements Serializable {

    @Id @GeneratedValue
    @Column(name = "ID")
    private int id;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "USER_ID")
    private User user;

    @Column(name = "PASSPORT_NO")
    private String passportNumber;

    @Column(name = "_LENGTH")
    private int lengthOfRent;

    @Column(name = "PAID")
    private boolean wasPaid;

    @OneToOne(fetch = FetchType.EAGER)
    private Car car;

    @OneToMany(fetch = FetchType.LAZY, mappedBy = "order")
    private Set<Bill> bills = new HashSet<Bill>();

    public Order() {}

    public Order(User user, String passportNumber, int lengthOfRent, boolean wasPaid, Car car) {
        this.user = user;
        this.passportNumber = passportNumber;
        this.lengthOfRent = lengthOfRent;
        this.wasPaid = wasPaid;
        this.car = car;
    }

    public int getId() {
        return id;
    }

    public User getUser() {
        return user;
    }
    public void setUser(User user) {
        this.user = user;
    }

    public String getPassportNumber() {
        return passportNumber;
    }
    public void setPassportNumber(String passportNumber) {
        this.passportNumber = passportNumber;
    }

    public int getLengthOfRent() {
        return lengthOfRent;
    }
    public void setLengthOfRent(int lengthOfRent) {
        this.lengthOfRent = lengthOfRent;
    }

    public boolean isWasPaid() {
        return wasPaid;
    }
    public void setWasPaid(boolean wasPaid) {
        this.wasPaid = wasPaid;
    }

    public Car getCar() {
        return car;
    }
    public void setCar(Car car) {
        this.car = car;
    }

    public Set<Bill> getBills() {
        return bills;
    }
    public void setBills(Set<Bill> bills) {
        this.bills = bills;
    }
}
