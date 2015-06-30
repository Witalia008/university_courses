package sample;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Date;
import java.util.zip.DataFormatException;

/**
 * Created by Witalia on 29.11.14.
 */
public class FileGetServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.sendRedirect("index.jsp");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        final String suffix = request.getParameter("suffix");
        if (suffix == null || request.getSession().getAttribute("user") == null) {
            response.sendRedirect("index.jsp");
            return;
        }

        String webapp = getServletContext().getRealPath("");
        File folder = new File(webapp + "/resources/data");
        File[] files = folder.listFiles(
                (dir, name)->name.endsWith(suffix));

        Date date = new Date();
        request.getSession().setAttribute("timeSpent", date.getTime() -
                ((Date) request.getSession().getAttribute("loginTime")).getTime());
//        System.out.println(Arrays.toString(folder.list()));

        Cookie cookie = new Cookie(
                "hw17_result_" + date.getTime() + "_" + suffix,
                ((Integer) FileUtils.getWordsCount(files)).toString());
        cookie.setMaxAge(60 * 5);   // store for 5 minutes
        response.addCookie(cookie);

        response.sendRedirect("files.jsp");
    }
}
