<%@ taglib prefix="s" uri="/struts-tags" %>
<%@ taglib prefix="sx" uri="/struts-dojo-tags" %>
<%--
  Created by IntelliJ IDEA.
  User: Witalia
  Date: 27.01.2015
  Time: 13:55
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
    <head>
        <sx:head/>
    </head>
    <body>
        <h4>
            Hello, <s:property value="username"/> <s:property value="surname"/><br/>
            <b><s:property value="id"/><br/></b>
            <s:property value="phoneNumber"/><br/>
            <s:property value="birthDate"/><br/>
            <s:property value="city"/><br/>
            <s:property value="address"/><br/>
            <s:property value="registered"/><br/>
        </h4>
    </body>
</html>
