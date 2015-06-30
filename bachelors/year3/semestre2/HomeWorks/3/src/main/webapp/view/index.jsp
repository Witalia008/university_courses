<%@ page contentType="text/html; charset=UTF-8" language="java" %>
<%@ taglib prefix="s" uri="/struts-tags" %>
<%@ taglib prefix="sx" uri="/struts-dojo-tags" %>
<html>
    <head>
        <sx:head/>
    </head>
    <body>
        <h2>Register</h2>
        <s:form action="Welcome">
            <s:textfield name="username" label="Name"/>
            <s:textfield name="surname" label="Surname"/>
            <s:password name="password" label="Password"/>
            <s:textfield name="phoneNumber" label="Phone"/>
            <sx:datetimepicker name="birthDate" label="Birth Date"
                               displayFormat="yyyy-MM-dd" value="%{'2010-01-01'}"/>
            <s:textfield name="city" label="Home City"/>
            <s:textfield name="address" label="Address"/>
            <s:submit/>
        </s:form>
    </body>
</html>
