<%@ page import="java.io.File" %>
<%@ page contentType="text/html; charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="udf" uri="http://localhost/21/mytlds" %>
<%@ page isELIgnored="false" %>
<hmtl>
    <head>
        <title>Gimme file</title>
    </head>
    <body>
        <c:choose>
            <c:when test="${not empty param.url}">
                <c:choose>
                    <c:when test="${udf:fileExists(param.url)}">
                        <c:redirect url="${'/sender'}">
                            <c:param name="filePath"
                                   value="${param.url}"/>
                        </c:redirect>
                    </c:when>
                    <c:otherwise>
                        <c:out value="No such file"/>
                    </c:otherwise>
                </c:choose>
            </c:when>
            <c:otherwise>
                <form action="/21" method="get">
                    <input type="text" name="url" />
                    <input type="submit" value="Get File"/>
                </form>
            </c:otherwise>
        </c:choose>
    </body>
</hmtl>