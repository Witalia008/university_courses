<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
    <head>
        <title>File finder</title>
        <link rel="stylesheet" href="resources/css/common.css" type="text/css"/>
    </head>
    <body>
        <%--<div class="container">
            <a href="#" class="button"><span>✓</span>Look I'm a button</a>
            <a href="#" class="button orange active"><span>✓</span>Look I'm a Active Button</a>
            <a href="#" class="button purple"><span>✓</span>Look I'm a button</a>
            <a href="#" class="button turquoise"><span>✓</span>Look I'm a button</a>
            <a href="#" class="button red"><span>✓</span>Look I'm a button</a>
        </div>--%>
        <c:choose>
            <c:when test="${sessionScope.user ne null}">
                <div>
                    Username:<br/>
                    <c:out value="${sessionScope.user.getUsername()}"/><br/>
                    Login Time:<br/>
                    <c:out value="${sessionScope.loginTime}"/><br/>
                    Online Time:<br/>
                    <c:out value="${sessionScope.timeSpent / 100}sec."/><br/>
                </div>
                <form action="getfiles" method="get">
                    Suffix:<br/>
                    <input type="text" name="suffix"/>
                    <input type="submit"/>
                </form>
            </c:when>
            <c:otherwise>
                <div style="margin: 20% auto; align-content: center;">
                    <form action="login" method="post">
                        Username:<br/>
                        <input type="text" name="username"/><br/>
                        Password:<br/>
                        <input type="password" name="password"/><br/>
                        <input type="submit" value="Login">
                    </form>
                </div>
            </c:otherwise>
        </c:choose>
        <a href="files.jsp">My Results</a>
    </body>
</html>