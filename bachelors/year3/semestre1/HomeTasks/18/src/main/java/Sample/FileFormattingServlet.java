package Sample;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;
import java.util.*;

/**
 * Created by Witalia on 31.10.2014.
 */
public class FileFormattingServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        throw new ServletException("Can't do GET request");
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

        PrintWriter out = resp.getWriter();
        resp.setContentType("text/html");

        if (ServletFileUpload.isMultipartContent(req)) {
            out.println("<textarea style=\"resize: vertical\" cols=\"80\" rows=\"30\">");

            ServletFileUpload upload = new ServletFileUpload(
                    new DiskFileItemFactory()
            );
            TextFormatter formatter = new TextFormatter(3, 80);

            try {
                List fileItems = upload.parseRequest(req);
                Iterator i = fileItems.iterator();

                while (i.hasNext()) {
                    FileItem fi = ((FileItem) i.next());
                    if (!fi.isFormField()) {
                        BufferedReader in = new BufferedReader(
                                new InputStreamReader(fi.getInputStream())
                        );
                        formatter.format(in, out);
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            out.println("</textarea>");
        }
    }
}
