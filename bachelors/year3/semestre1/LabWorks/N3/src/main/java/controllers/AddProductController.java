package controllers;

import dbtools.DBCachePool;
import ents.Product;
import ents.Role;
import ents.User;
import org.apache.log4j.Logger;
import repo.ProductRepo;
import repo.RoleRepo;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * Created by Witalia on 25.11.2014.
 */
public class AddProductController extends HttpServlet {
    private static Logger logger = Logger.getLogger(AddProductController.class);
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        logger.error("Add Product can't do GET request");
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        User user = (User) req.getSession().getAttribute("user");
        if (user == null || RoleRepo.getUserRole(
                DBCachePool.getInstance(), user) != Role.ADMIN) {
            resp.sendRedirect("index.jsp");
            return;
        }
        Product product = new Product();
        String id = req.getParameter("id");
        if (id != null && id != "") {
            product.setId(Integer.parseInt(id));
        }
        product.setName(req.getParameter("name"));
        product.setType(req.getParameter("type"));
        product.setDescription(req.getParameter("description"));
        product.setPrice(Integer.valueOf(req.getParameter("price")));
        if (ProductRepo.add(DBCachePool.getInstance(), product) == true) {
            resp.sendRedirect("products.jsp");
        } else {
            resp.getWriter().println("Can't add");
        }
    }
}
