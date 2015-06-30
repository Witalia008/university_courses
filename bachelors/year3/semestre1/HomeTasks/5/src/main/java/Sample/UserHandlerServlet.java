package Sample;

import Sample.utils.Database;
import Sample.utils.User;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * Created by Witalia on 18.11.2014.
 */
public class UserHandlerServlet extends HttpServlet {
    private final static Database database =
            Database.getDatabase("Witalia", "password");

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession();
        PrintWriter out = response.getWriter();
        response.setContentType("text/html");

        String register = request.getParameter("register");
        String userName = request.getParameter("username");
        String password = request.getParameter("password");
        User user = new User(userName, password);

        if (register != null && register.equals("on")) {
            if (database.addUser(user)) {
                out.println("You have been successfully registered."
                        + " Please return to previous page to log in.");
            } else {
                out.println("Seems like username is already taken."
                        + " Please choose another one.");
            }
        } else {
            if (database.checkCredentials(user)) {
                session.setAttribute("user", user);
                response.sendRedirect("/5/storage.jsp");
            } else {
                out.println("Wrong username/password. Please try again.");
            }
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        throw new ServletException("GET requests are not supported");
    }
}
