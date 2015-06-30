package db.beans;

import javax.persistence.*;

/**
 * Created by Witalia on 09.12.2014.
 */
@Entity
@Table(name = "messages")
public class Message {
    @Id @GeneratedValue
    @Column(name = "id")
    private int id;

    @Column(name = "text")
    private String text;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "room")
    private Room room;

    @ManyToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "usr")
    private User user;

    public Message(String text, Room room, User user) {
        this.text = text;
        this.room = room;
        this.user = user;
    }

    public Message() {
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public Room getRoom() {
        return room;
    }

    public void setRoom(Room room) {
        this.room = room;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }
}
