<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>

</head>
<body>
<%
    Cookie[] cookies = request.getCookies();
    for (Cookie cookie : cookies) {
        if (cookie.getName().startsWith("hw17_result_")) {
            out.println(cookie.getName() + " = "
                    + cookie.getValue() + "<br/>");
        }
    }
%>
<a href="index.jsp">&lt; back</a>
</body>
</html>
