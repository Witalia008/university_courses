package sample;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.Date;

/**
 * Created by Witalia on 29.11.14.
 */
public class LoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        HttpSession session = req.getSession();
        User user = new User(
                req.getParameter("username"),
                req.getParameter("password")
        );
        session.setAttribute("user", user);
        session.setAttribute("loginTime", new Date());
        session.setAttribute("timeSpent", 0);
        resp.sendRedirect("index.jsp");
    }
}
