package Sample;

import org.apache.commons.io.FileUtils;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.IOException;

/**
 * Created by Witalia on 19.11.2014.
 */
public class FileSenderServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        String filePath = req.getParameter("filePath");
        resp.setContentType("application/octet-stream");
        resp.setHeader("Content-Disposition", "filename=\"" +
                filePath.substring(filePath.lastIndexOf("\\") + 1) + "\"");
        File f = new File(filePath);
        FileUtils.copyFile(f, resp.getOutputStream());
    }
}
