<%@ tag import="repo.RoleRepo" %>
<%@ tag import="ents.Role" %>
<%@ tag import="dbtools.DBCachePool" %>
<%@ tag body-content="scriptless" %>
<%@ attribute name="user" required="true" type="ents.User" rtexprvalue="true" %>
<%@ attribute name="role" required="true" type="java.lang.String" rtexprvalue="true" %>
<%@ attribute name="is" required="false" type="java.lang.Boolean" rtexprvalue="true" %>
<%
    boolean cond = false;
    if (role.charAt(0) == '!') {
        role = role.substring(1);
        cond = true;
    }
    if (cond ^ (RoleRepo.getUserRole(DBCachePool.getInstance(), user) == Role.valueOf(role))) {
        %> <jsp:doBody/> <%
    }
%>

