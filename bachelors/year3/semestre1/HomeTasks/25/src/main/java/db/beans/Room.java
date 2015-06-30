package db.beans;

import javax.persistence.*;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by Witalia on 09.12.2014.
 */
@Entity
@Table(name = "rooms")
public class Room {
    @Id
    @GeneratedValue
    @Column(name = "id")
    private int id;

    @Column(name = "topic")
    private String topic;

    @OneToMany(fetch = FetchType.LAZY, mappedBy = "room")
    private Set<User> users = new HashSet<>();

    @OneToMany(fetch = FetchType.LAZY, mappedBy = "room")
    private Set<Message> messages = new HashSet<>();

    public Room() {
    }

    public Room(String topic) {
        this.topic = topic;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getTopic() {
        return topic;
    }

    public void setTopic(String topic) {
        this.topic = topic;
    }

    public Set<User> getUsers() {
        return users;
    }

    public void setUsers(Set<User> users) {
        this.users = users;
    }

    public Set<Message> getMessages() {
        return messages;
    }

    public void setMessages(Set<Message> messages) {
        this.messages = messages;
    }
}
