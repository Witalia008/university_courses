<%@ taglib prefix="ex" uri="localmin"%>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions" %>
<%@ page isELIgnored="false"%>

<html>
    <head>
        <title>Get local minimums</title>
    </head>
    <body>
        <ex:minimums array="${ex:strArrToIntArr(fn:split(param.array, ','))}"/><br/>
        <ex:maximums array="${ex:strArrToIntArr(fn:split(param.array, ','))}"/><br/>

        <script src="resources/js/arrayhandler.js"></script>
        <form>
            <input type="number" id="num">
            <input type="button" value="<>" onclick="createRows()"><br/>
            <table id="inputTable">
            </table>
            <input type="hidden" id="result" name="array"/>
            <input type="submit" onclick="inArray()"><br/>
        </form>
    </body>
</html>
