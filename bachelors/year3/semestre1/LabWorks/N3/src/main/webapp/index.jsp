<%@ page contentType="text/html; UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="cst" tagdir="/WEB-INF/tags" %>
<%@ page isELIgnored="false" %>
<html>
    <head>
        <title>Login page</title>
        <link rel="stylesheet" href="resources/css/common.css" type="text/css"/>
    </head>
    <body>
        <div class="centered_div">
        <c:choose>
            <c:when test="${sessionScope.user eq null}">
                <form action="login" method="post">
                    Username:<br/>
                    <input type="text" name="username"/><br/>
                    Password:<br/>
                    <input type="password" name="password"/><br/>
                    New user?
                    <input type="checkbox" name="register"><br/>
                    <input type="submit" class="button-link"/>
                </form>
            </c:when>
            <c:otherwise>
                <c:out value="You are already logged in"/><br/>
                <a href="products.jsp">Products</a><br/>
                <a href="cart.jsp">To my Cart</a>
                <cst:role user="${sessionScope.user}" role="ADMIN">
                    <a href="users.jsp"/><br/>
                </cst:role>
            </c:otherwise>
        </c:choose>
        </div>
    </body>
</html>
