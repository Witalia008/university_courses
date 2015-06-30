package controllers;

import dbtools.DBCachePool;
import ents.Order;
import ents.User;
import org.apache.log4j.Logger;
import repo.OrderRepo;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * Created by Witalia on 25.11.2014.
 */
public class AddOrderController extends HttpServlet {
    private Logger logger = Logger.getLogger(AddOrderController.class);

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        User user = ((User) request.getSession().getAttribute("user"));
        if (user == null) {
            response.sendRedirect("index.jsp");
            return;
        }
        Order order = new Order();
        order.setUserId(user.getId());
        order.setProductId(Integer.parseInt(request.getParameter("productId")));
        order.setAmount(Integer.parseInt(request.getParameter("amount")));
        order.setTotal(Integer.parseInt(request.getParameter("price"))
                            * order.getAmount());
        if (OrderRepo.add(DBCachePool.getInstance(), order) == true) {
            response.sendRedirect("products.jsp");
        } else {
            response.getWriter().println("Something went wrong");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        logger.error("Add Order can't do GET requests");
    }
}
