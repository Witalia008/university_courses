<!
<%@ page import="ents.Product" %>
<%@ page import="repo.ProductRepo" %>
<%@ page import="dbtools.DBCachePool" %>
<%--
  Created by IntelliJ IDEA.
  User: Witalia
  Date: 24.11.2014
  Time: 19:52
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="cst" tagdir="/WEB-INF/tags" %>
<%@ page isELIgnored="false" %>
<html>
    <head>
        <title>Product list</title>
        <link rel="stylesheet" href="resources/css/tables.css" type="text/css"/>
        <meta charset="UTF-8"/>
    </head>
    <body>
        <c:if test="${sessionScope.user eq null}">
            <c:redirect url="index.jsp"/>
        </c:if>
        <cst:userinfo user="${sessionScope.user}"/>
        <%-- Show all products --%>
        <%
            Product[] products = ProductRepo.getAllProducts(DBCachePool.getInstance());
            pageContext.setAttribute("products", products);
        %>
        <table border="1">
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Type</th>
                    <th>Name</th>
                    <th>Description</th>
                    <th>Price</th>
                    <th>Order</th>
                </tr>
            </thead>
            <tbody>
                <c:forEach var="cur" items="${pageScope.products}">
                    <cst:product product="${cur}"/>
                </c:forEach>
                <cst:role user="${sessionScope.user}" role="ADMIN">
                    <tr>
                        <form action="addproduct" method="post">
                            <td><input type="number" name="id"></td>
                            <td><input type="text" name="type"></td><input type="">
                            <td><input type="text" name="name"></td>
                            <td><textarea name="description"></textarea></td>
                            <td><input type="number" name="price"></td>
                            <td><input type="submit" value="Add"></td>
                        </form>
                    </tr>
                </cst:role>
            </tbody>
        </table>
        <cst:role user="${sessionScope.user}" role="ADMIN">
            <a href="users.jsp">Users</a>
            <a href="orders.jsp">Orders</a>
            <a href="cart.jsp">To my Cart</a>
        </cst:role>
    </body>
</html>
