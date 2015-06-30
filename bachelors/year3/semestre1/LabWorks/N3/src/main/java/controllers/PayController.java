package controllers;

import dbtools.DBCachePool;
import ents.User;
import org.apache.log4j.Logger;
import repo.OrderRepo;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * Created by Witalia on 26.11.2014.
 */
public class PayController extends HttpServlet {
    private static Logger logger = Logger.getLogger(PayController.class);

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        logger.error("Pay can't process GET request");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        User user = ((User) request.getSession().getAttribute("user"));
        if (user == null) {
            response.sendRedirect("index.jsp");
            return;
        }
        OrderRepo.deleteByUserId(DBCachePool.getInstance(), user);
        response.sendRedirect("products.jsp");
    }
}
