<%@ tag body-content="empty" %>
<%@ attribute name="user" required="true" type="ents.User" rtexprvalue="true" %>
<link rel="stylesheet" href="resources/css/common.css" type="text/css"/>
<form action="logout" method="post">
    You logged in as <i><%= user.getUsername() %></i>
    <input type="submit" class="button-link" value="Log out"/><br/>
</form>
