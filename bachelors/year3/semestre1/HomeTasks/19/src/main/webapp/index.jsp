<%@ page contentType="text/html; UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="ex" uri="points" %>
<%@ page isELIgnored="false" %>
<html>
    <head>
        <script src="resources/js/arrayhandler.js"></script>
        <title>Points finder</title>
    </head>
    <body>
        <ex:maxpt array="${param.array}" ptX="${param.pX}" ptY="${param.pY}"/>
        <form>
            X:<input type="number" name="pX"><br/>
            Y:<input type="number" name="pY"><br/>
            Enter 5 radii:<br/>
            <table id="inputTable">
                <c:forEach begin="1" end="5">
                    <tr><td><input type="number"/></td></tr>
                </c:forEach>
            </table>
            <input type="hidden" id="result" name="array"/>
            <input type="submit" onclick="inArray()"/>
        </form>
    </body>
</html>
