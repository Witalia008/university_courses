<%@ page import="ents.Order" %>
<%@ page import="repo.OrderRepo" %>
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
        <title>All users</title>
        <link rel="stylesheet" href="resources/css/tables.css" type="text/css"/>
    </head>
    <body>
        <c:if test="${sessionScope.user eq null}">
            <c:redirect url="index.jsp"/>
        </c:if>
        <%-- Check if user is admin --%>
        <cst:role user="${sessionScope.user}" role="!ADMIN">
            <c:redirect url="products.jsp"/>
        </cst:role>
        <cst:userinfo user="${sessionScope.user}"/>
        <%-- Show users from database here --%>
        <%
            Order[] orders = OrderRepo.getAll(DBCachePool.getInstance());
            pageContext.setAttribute("orders", orders);
        %>
        <table border="1">
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Product</th>
                    <th>User</th>
                    <th>Amount</th>
                    <th>Total</th>
                </tr>
            </thead>
            <tbody>
                <c:forEach var="cur" items="${orders}">
                    <cst:order order="${cur}"/>
                </c:forEach>
            </tbody>
        </table>
        <a href="users.jsp">Users</a>
        <a href="products.jsp">Products</a>
        <a href="cart.jsp">To my Cart</a>
    </body>
</html>
