import java.util.HashMap;
import java.util.Map;

/**
 * Created by Witalia on 24.11.2014.
 */
public class Main {
    public static void main(String[] args) {
        System.out.println(babyStepGiantStep(14, 5, 29));
    }

    public static long babyStepGiantStep(long a, long b, long m) {
        long n = (long) (Math.sqrt(m + .0) + 1);
        // a ^ x = b (mod m)
        // x = n * p - q
        // a ^ (n * p - q) = b (mod m)
        // a ^ (n * p) = b * a ^ q (mod m)

        long an = 1;
        for (int i = 0; i < n; ++i) {
            an = (an * a) % m;
        }

        Map<Long, Long> M = new HashMap<Long, Long>();
        for (long p = 1, cur = an; p <= n; ++p) {
            if (M.containsKey(cur) == false) {
                M.put(cur, p);
            }
            cur = (cur * an) % m;
        }

        for (long q = 0, cur = b; q < n; ++q) {
            if (M.containsKey(cur)) {
                long res = M.get(cur) * n - q;
                if (res < m) {
                    return res;
                }
            }
            cur = (cur * a) % m;
        }
        return -1;
    }
}
