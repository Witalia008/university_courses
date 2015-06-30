import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.*;

/**
 * Created by Witalia on 25.03.2015.
 */
public class MyServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request,
                         HttpServletResponse response)
            throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        response.setContentType("text/html");
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Products</title>");
        out.println("<link href =\"css/newcss.css\""+
                "rel=\"stylesheet\" type=\"text/css\">");
        out.println("</head>");
        out.println("<body>");
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/STOCK",
                    "user",
                    "password"
            );
            PreparedStatement statement = connection.prepareStatement(
                    "SELECT * FROM categories INNER JOIN products ON categories.ID_CAT = products.ID_CAT"
            );
            ResultSet res = statement.executeQuery();
            out.println("<table>");
            int colCount = res.getMetaData().getColumnCount();
            out.println("<tr>");
            for (int i = 0; i < colCount; i++) {
                out.println("<th>");
                out.println(res.getMetaData().getColumnName(i + 1));
                out.println("</th>");
            }
            out.println("</tr>");
            while (res.next()) {
                out.println("<tr>");

                for (int i = 0; i < colCount; i++) {
                    out.println(i == 0 ? "<th>" : "<td>");
                    out.println(res.getObject(i + 1));
                    out.println(i == 0 ? "</th>" : "</td>");
                }

                out.println("</tr>");
            }
            out.println("</body>");
            out.println("</table>");
            res.close();
            connection.close();
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
    }
}
