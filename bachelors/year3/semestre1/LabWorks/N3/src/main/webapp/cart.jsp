<%@ page import="ents.Order" %>
<%@ page import="repo.OrderRepo" %>
<%@ page import="dbtools.DBCachePool" %>
<%@ page import="ents.User" %>
<%--
  Created by IntelliJ IDEA.
  User: Witalia
  Date: 26.11.2014
  Time: 9:20
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="cst" tagdir="/WEB-INF/tags" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<html>
    <head>
        <title>Cart</title>
        <link rel="stylesheet" href="resources/css/tables.css" type="text/css"/>
        <link rel="stylesheet" href="resources/css/common.css" type="text/css"/>
    </head>
    <body>
        <c:if test="${sessionScope.user eq null}">
            <c:redirect url="index.jsp"/>
        </c:if>
        <cst:userinfo user="${sessionScope.user}"/>
        <%
            Order[] orders = OrderRepo.getByUserId(DBCachePool.getInstance(),
                    ((User) request.getSession().getAttribute("user")));
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
                <tr>
                    <td colspan="5">
                        <form action="pay" method="post">
                            <input class="button-link" type="submit" value="Pay!">
                        </form>
                    </td>
                </tr>
            </tbody>
        </table>
        <a href="products.jsp">Products</a>
        <cst:role user="${sessionScope.user}" role="ADMIN">
            <a href="orders.jsp">Orders</a>
            <a href="users.jsp">Users</a>
        </cst:role>
    </body>
</html>
