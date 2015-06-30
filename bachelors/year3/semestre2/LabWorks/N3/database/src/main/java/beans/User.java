package beans;

import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by Witalia on 04.04.2015.
 */
@Entity
@Table(name = "users")
public class User implements Serializable {

    @Id @GeneratedValue
    @Column(name = "ID")
    private int id;

    @Column(name = "_NAME")
    private String name;

    @Column(name = "_PASS")
    private String password;

    @OneToMany(fetch = FetchType.EAGER, mappedBy = "user")
    private Set<Role> roles = new HashSet<Role>();

    @OneToMany(fetch = FetchType.LAZY, mappedBy = "user")
    private Set<Order> orders = new HashSet<Order>();

    public User() {    }

    public User(String name, String password) {
        this.name = name;
        this.password = password;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }

    public String getPassword() {
        return password;
    }
    public void setPassword(String password) {
        this.password = password;
    }

    public Set<Role> getRoles() {
        return roles;
    }
    public void setRoles(Set<Role> roles) {
        this.roles = roles;
    }

    public Set<Order> getOrders() {
        return orders;
    }
    public void setOrders(Set<Order> orders) {
        this.orders = orders;
    }
}
