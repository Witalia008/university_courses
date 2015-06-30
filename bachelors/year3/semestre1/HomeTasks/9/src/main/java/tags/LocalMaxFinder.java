package tags;

import javax.servlet.jsp.JspException;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.tagext.SimpleTagSupport;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Witalia on 22.11.2014.
 */
public class LocalMaxFinder extends SimpleTagSupport {
    private Object array;

    public void setArray(Object array) {
        this.array = array;
    }

    @Override
    public void doTag() throws JspException, IOException {
        JspWriter out = getJspContext().getOut();
        out.println("<table><tr>");
        if (array != null && (array instanceof Integer[])) {
            Integer[] a = getMaxs();
            for (Integer cur : a) {
                out.print("<td>" + cur + "</td>");
            }
        }
        out.println("</tr></table>");
        out.println();
    }
    public Integer[] getMaxs() {
        List<Integer> res = new ArrayList<>();
        Integer[] arr = ((Integer[]) array);
        for (int i = 0; i < arr.length; i++) {
            Integer cur = arr[i];
            if ((i == 0 || arr[i - 1] <= cur)
                    && (i == arr.length - 1 || arr[i + 1] <= cur)) {
                res.add(cur);
            }
        }
        return res.toArray(new Integer[res.size()]);
    }
}
