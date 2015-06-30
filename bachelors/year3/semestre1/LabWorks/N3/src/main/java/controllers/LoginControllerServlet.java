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
import java.io.PrintWriter;

/**
 * Created by Witalia on 24.11.2014.
 */
public class LoginControllerServlet extends HttpServlet {
    private static Logger logger = Logger.getLogger(LoginControllerServlet.class);

    /**
     * Get requests are not supported by this controller
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        logger.error("Login can't process GET requests");
        resp.sendRedirect("index.jsp");
    }

    /**
     * Control login request.
     * If user wants to register - check login availability and,
     * if success - register.
     * If user wants to login - check entered credentials and,
     * if correct - login and redirect to some page.
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        PrintWriter out = resp.getWriter();
        User user = new User(
                req.getParameter("username"),
                req.getParameter("password")
        );
        DBCachePool pool = DBCachePool.getInstance();

        String register = req.getParameter("register");
        if (register != null && register.equals("on")) {
            // Register new user
            if (UserRepo.checkExists(pool, user) == true) {
                out.println("User with such nickname already exists");
            } else {
                if (UserRepo.register(pool, user)) {
                    logger.info("Registered user " + user.getId());
                    resp.sendRedirect("index.jsp");
                } else {
                    out.println("There was some error");
                }
            }
        } else {
            // Login
            if (UserRepo.checkCredentials(pool, user) == true) {
                if (RoleRepo.getUserRole(pool, user) == Role.BLOCKED) {
                    out.println("Sorry, you were banned.");
                } else {
                    req.getSession().setAttribute("user", user);
                    resp.sendRedirect("products.jsp");
                }
            } else {
                out.println("Wrong username or password");
            }
        }
    }
}
