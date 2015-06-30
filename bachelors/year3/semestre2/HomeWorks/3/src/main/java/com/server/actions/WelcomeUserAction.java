package com.server.actions;

import com.server.db.UserRepo;

import java.util.Date;

/**
 * Created by Witalia on 27.01.2015.
 */
public class WelcomeUserAction {
    private Integer id;
    private String username;
    private String surname;
    private String password;
    private String phoneNumber;
    private String city;
    private String address;
    private Date birthDate;
    private Date registered;


    public String execute() {
        registered = new Date();
        if (UserRepo.getIdByName(username, surname) == -1 && UserRepo.addUser(this)) {
            this.id = UserRepo.getIdByName(username, password);
            return "success";
        }
        return "fail";
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Date getRegistered() {
        return registered;
    }

    public void setRegistered(Date registered) {
        this.registered = registered;
    }

    public Date getBirthDate() {
        return birthDate;
    }

    public void setBirthDate(Date birthDate) {
        this.birthDate = birthDate;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public String getSurname() {
        return surname;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getPassword() {
        return password;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getCity() {
        return city;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getAddress() {
        return address;
    }
}
