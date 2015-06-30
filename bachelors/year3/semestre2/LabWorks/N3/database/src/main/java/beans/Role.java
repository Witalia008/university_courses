package beans;

import javax.persistence.*;
import java.io.Serializable;

/**
 * Created by Witalia on 04.04.2015.
 */
@Entity
@Table(name = "roles")
public class Role implements Serializable {

    @Id @GeneratedValue
    @Column(name = "ID")
    private int id;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "USER_ID")
    private User user;

    @Column(name = "ROLE")
    private String roleName;

    public Role() {    }

    public Role(User user, String roleName) {
        this.user = user;
        this.roleName = roleName;
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

    public String getRoleName() {
        return roleName;
    }
    public void setRoleName(String roleName) {
        this.roleName = roleName;
    }
}
