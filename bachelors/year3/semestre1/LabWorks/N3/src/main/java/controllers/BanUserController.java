package controllers;

import dbtools.DBCachePool;
import ents.Role;
import ents.User;
import org.apache.log4j.Logger;
import repo.RoleRepo;
import repo.UserRepo;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * Created by Witalia on 25.11.2014.
 */
public class BanUserController extends HttpServlet {
    private static Logger logger = Logger.getLogger(BanUserController.class);

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        logger.error("Ban user can't do GET requests");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        User user = (User) request.getSession().getAttribute("user");
        if (user == null || RoleRepo.getUserRole(
                DBCachePool.getInstance(), user) != Role.ADMIN) {
            response.sendRedirect("index.jsp");
        }
        DBCachePool pool = DBCachePool.getInstance();
        User user1 = UserRepo.getByID(pool, Integer.parseInt(request.getParameter("id")));
        if (user1 != user) {
            if (RoleRepo.getUserRole(pool, user1) == Role.BLOCKED) {
                RoleRepo.addOrUpdateRole(pool, user1, Role.USER);
            } else {
                RoleRepo.addOrUpdateRole(pool,
                        user1,
                        Role.BLOCKED);
            }
        }
        response.sendRedirect("users.jsp");
    }
}
