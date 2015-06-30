package com.server.db;

import com.server.actions.WelcomeUserAction;

import java.sql.*;

/**
 * Created by Witalia on 28.01.2015.
 */
public class UserRepo {
    public static int getIdByName(String name, String surname) {
        try {
            Connection connection = DBCachePool.getInstance().getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "select id from oop_c3_ii_hw3.user where user_name = ? and user_surname = ?"
            );
            statement.setString(1, name);
            statement.setString(2, surname);
            ResultSet res = statement.executeQuery();
            if (res.next()) {
                return res.getInt(1);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -1;
    }

    public static boolean addUser(WelcomeUserAction user) {
        try {
            Connection connection = DBCachePool.getInstance().getConnection();
            PreparedStatement statement = connection.prepareStatement(
                    "insert into oop_c3_ii_hw3.user values (default, ?, ?, ?, ?, ?, ?, ?, ?)"
            );
            statement.setString(1, user.getUsername());
            statement.setString(2, user.getSurname());
            statement.setString(3, user.getPhoneNumber());
            statement.setDate(4, new Date(user.getBirthDate().getTime()));
            statement.setString(5, user.getCity());
            statement.setString(6, user.getAddress());
            statement.setDate(7, new Date(user.getRegistered().getTime()));
            statement.setString(8, user.getPassword());
            statement.executeUpdate();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }
}
