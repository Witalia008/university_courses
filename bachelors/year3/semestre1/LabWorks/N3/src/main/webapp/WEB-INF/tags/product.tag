<%@ tag body-content="empty" %>
<%@ attribute name="product" required="true" type="ents.Product" rtexprvalue="true" %>

<tr>
    <td width="5%"><%= product.getId() %></td>
    <td width="10%"><%= product.getType()%></td>
    <td width="10%"><%= product.getName()%></td>
    <td width="65%"><%= product.getDescription()%></td>
    <td width="10%"><%= product.getPrice()%>$</td>
    <td>
        <form action="addorder" method="post">
            Amount:
            <input type="number" name="amount"/>
            <input type="hidden" name="productId" value="<%=product.getId()%>">
            <input type="hidden" name="price" value="<%=product.getPrice()%>">
            <input type="submit" value="Order">
        </form>
    </td>
</tr>
