<%@ tag import="repo.ProductRepo" %>
<%@ tag import="dbtools.DBCachePool" %>
<%@ tag import="repo.UserRepo" %>
<%@ tag body-content="empty" %>
<%@ attribute name="order" required="true" type="ents.Order" rtexprvalue="true" %>

<tr>
    <td width="20%"><%= order.getId() %></td>
    <td width="20%">
        <%= ProductRepo.getByID(
                DBCachePool.getInstance(),
                order.getProductId()).getName()
        %>
    </td>
    <td width="20%">
        <%= UserRepo.getByID(
                DBCachePool.getInstance(),
                order.getUserId()).getUsername()%>
    </td>
    <td width="20%"><%= order.getAmount() %></td>
    <td width="20%"><%= order.getTotal() %>$</td>
</tr>
