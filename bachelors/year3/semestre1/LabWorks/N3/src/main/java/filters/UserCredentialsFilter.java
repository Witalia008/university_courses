package filters;

import javax.servlet.*;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * Created by Witalia on 26.11.2014.
 */

/**
 * Class for catching wrong credentials before sending to server
 */
public class UserCredentialsFilter implements Filter {
    public void destroy() {
    }

    /**
     * Check if username and password are good
     * @param req
     * @param resp
     * @param chain
     * @throws ServletException
     * @throws IOException
     */
    public void doFilter(ServletRequest req,
                         ServletResponse resp,
                         FilterChain chain)
            throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if (username.length() < 3 || password.length() < 4) {
            ((HttpServletResponse) resp).sendRedirect("index.jsp");
            return;
        }
        chain.doFilter(req, resp);
    }

    public void init(FilterConfig config) throws ServletException {

    }

}
