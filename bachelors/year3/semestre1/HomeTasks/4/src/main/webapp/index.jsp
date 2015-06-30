<%--
  Created by IntelliJ IDEA.
  User: Witalia
  Date: 03.11.2014
  Time: 12:53
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="Sample.Main" %>
<%@ page import="java.io.FileInputStream" %>
<%@ page import="java.io.File" %>
<%= request.getHeader("user-agent") %>
<%
    String folder = application.getRealPath("") + "\\";
    File xml = new File(folder + "data\\gems.xml");
    File xsd = new File(folder + "data\\gems.xsd");
    File xsl = new File(folder + "data\\gems.xsl");
    String content = "Wrong input data!";
    if (Main.validateAgainstXSD(new FileInputStream(xml), new FileInputStream(xsd))) {
        content = Main.convertToHTML(new FileInputStream(xml), new FileInputStream(xsl));
    }
%>
<%= content %>
