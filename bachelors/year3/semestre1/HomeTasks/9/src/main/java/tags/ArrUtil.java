package tags;

/**
 * Created by Witalia on 22.11.2014.
 */
public class ArrUtil {

    public static Integer[] toIntArr(String[] args) {
        try {
            Integer[] res = new Integer[args.length];
            for (int i = 0; i < res.length; i++) {
                res[i] = Integer.parseInt(args[i]);
            }
            return res;
        } catch (Exception e) {
            return null;
        }
    }
}
