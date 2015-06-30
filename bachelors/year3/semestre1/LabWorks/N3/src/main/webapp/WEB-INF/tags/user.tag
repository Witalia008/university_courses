<%@ tag import="repo.RoleRepo" %>
<%@ tag import="dbtools.DBCachePool" %>
<%@ tag body-content="empty" %>
<%@ attribute name="user" type="ents.User" required="true" rtexprvalue="true" %>
<tr>
    <td><%= user.getId() %></td>
    <td><%= user.getUsername() %></td>
    <td><%= RoleRepo.getUserRole(DBCachePool.getInstance(), user) %></td>
    <td>
        <form action="ban" method="post">
            <input type="hidden" name="id" value="<%=user.getId()%>"/>
            <input type="submit" value="Block/Unblock">
        </form>
    </td>
</tr>