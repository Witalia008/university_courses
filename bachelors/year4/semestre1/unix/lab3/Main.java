import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

/**
 * Created by witalia on 17.09.15.
 */
public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        if (args.length == 2) {
            File dir = new File(args[0]);
            List<File> lst = getContents(dir, args[1]);
            Collections.sort(
                    lst,
                    (a,b) -> a.length() < b.length() ? 1 : -1
            );

            Scanner sc = new Scanner(System.in);
            String outFile = sc.nextLine();
            PrintWriter wr = new PrintWriter(new BufferedOutputStream(new FileOutputStream(outFile)));
            for (File f : lst) {
                wr.println(f.length() + " " + f.getName());
            }
            wr.close();
        }
    }

    private static List<File> getContents(File f, String pref) {
        List<File> res = new ArrayList<>();
        if (!f.exists()) {
            return res;
        }
        if (f.isDirectory()) {
            for (File f1 : f.listFiles()) {
                res.addAll(getContents(f1, pref));
            }
        } else {
            if (f.getName().startsWith(pref)) {
                res.add(f);
            }
        }
        return res;
    }
}
