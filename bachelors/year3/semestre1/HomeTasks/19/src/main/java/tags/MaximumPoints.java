package tags;

import dbtools.Database;
import javafx.util.Pair;

import javax.servlet.jsp.JspException;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.tagext.SimpleTagSupport;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Created by Witalia on 22.11.2014.
 */
public class MaximumPoints extends SimpleTagSupport {
    private Object array;
    private Integer ptX = 0;
    private Integer ptY = 0;

    public void setArray(Object array) {
        this.array = array;
    }

    public void setPtX(Integer ptX) {
        this.ptX = ptX;
    }

    public void setPtY(Integer ptY) {
        this.ptY = ptY;
    }

    @Override
    public void doTag() throws JspException, IOException {
        JspWriter out = getJspContext().getOut();
        if (array == null || !(array instanceof String)) {
            return;
        }
        String[] arr = ((String) array).split(",");
        Integer[] a = new Integer[arr.length];
        for (int i = 0; i < a.length; i++) {
            a[i] = Integer.parseInt(arr[i]);
        }
        Arrays.sort(a);

        Pair p = Database.get();
        List ans = getDivision(p, a);

        printList(ans, out);
    }

    public List<Pair<Integer, Integer>> getDivision(Pair p, Integer[] a) {
        List<Integer> x = (List<Integer>) p.getKey();
        List<Integer> y = (List<Integer>) p.getValue();

        List[] res = new List[a.length + 1];
        for (int i = 0; i < res.length; i++) {
            res[i] = new ArrayList<Pair<Integer, Integer>>();
        }

        for (int i = 0; i < x.size(); i++) {
            res[getIndex(x.get(i), y.get(i), a)]
                    .add(new Pair<>(x.get(i), y.get(i)));
        }

        List ans = null;
        for (List l : res) {
            if (ans == null || l.size() > ans.size()) {
                ans = l;
            }
        }
        return ans;
    }

    private void printList(List a, JspWriter out) throws IOException {
        out.println("<table border=\"1\">");
        for (Object p : a) {
            int x = ((Pair<Integer, Integer>)p).getKey();
            int y = ((Pair<Integer, Integer>)p).getValue();
            out.print("<tr><td>");
            out.print(x);
            out.print("</td><td>");
            out.print(y);
            out.print("</tr></td>");
        }
        out.println("</table>");
    }

    private int getIndex(int x, int y, Integer[] radii) {
        Integer len = (ptX - x) * (ptX - x) + (ptY - y) * (ptY - y);
        int idx = radii.length - 1;
        while (idx >= 0 && radii[idx] * radii[idx] > len) {
            --idx;
        }
        return idx + 1;
    }
}
