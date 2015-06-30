package db.beans;

import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by Witalia on 09.12.2014.
 */
@Entity
@Table(name = "users")
public class User implements Serializable {
    @Id @GeneratedValue
    @Column(name = "id")
    private int id;

    @Column(name = "username")
    private String username;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "room")
    private Room room;

    @OneToMany(fetch = FetchType.LAZY, mappedBy = "user")
    private Set<Message> messages = new HashSet<>();

    public User() {
    }

    public User(String username, Room room) {
        this.username = username;
        this.room = room;
    }

    public int getId() {
        return id;
    }

    public Set<Message> getMessages() {
        return messages;
    }

    public void setMessages(Set<Message> messages) {
        this.messages = messages;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public Room getRoom() {
        return room;
    }

    public void setRoom(Room room) {
        this.room = room;
    }
}
