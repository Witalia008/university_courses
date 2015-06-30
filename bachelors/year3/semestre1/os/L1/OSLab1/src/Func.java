import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

/**
 * Created by Witalia on 9/30/2014.
 */
public class Func {
    public static void main(String[] args){
        int t = Integer.parseInt(args[0]);
        int r = Integer.parseInt(args[1]);
        if (t < 0) t = Integer.MAX_VALUE;
        try {
            Thread.sleep(t);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println(r);
    }
}
