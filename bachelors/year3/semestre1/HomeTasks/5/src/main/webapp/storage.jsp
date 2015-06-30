<%@ page import="java.io.File" %>
<%@ page import="Sample.utils.User" %>
<%--
  Created by IntelliJ IDEA.
  User: Witalia
  Date: 18.11.2014
  Time: 18:55
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
  <head>
    <%
      User user = (User) request.getSession().getAttribute("user");
      if (user == null) {
        response.sendRedirect("/5");
      }
      String folder = application.getRealPath("data\\" + user.getUsername());
      File userDir = new File(folder);
      if (userDir.exists() == false) {
        userDir.mkdir();
      }
    %>
    <title><%= user.getUsername()%>'s files</title>
  </head>
  <body>
    <%
      String[] files = userDir.list();
      for (int i = 0; i < files.length; i++) {
        String file = files[i];
        out.print("<a href=\"" + "data\\" + user.getUsername() + "\\" + file + "\">");
        out.print(file);
        out.println("</a><br/>");
      }
      if (files == null || files.length == 0) {
        out.println("Sorry, but it seems you don't have any files to download :(");
      }
    %>
  </body>
</html>
