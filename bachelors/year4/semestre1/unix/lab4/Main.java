import java.io.*;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

/**
 * Created by witalia on 17.09.15.
 */

public class Main {


    public static void main(String[] args) throws IOException {
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(new File("/home/witalia/Dropbox/Projects/neww/target/classes/"));
        pb.command("/home/witalia/Java/jdk1.8.0_60/bin/java", "SubMain");
        pb.redirectInput(ProcessBuilder.Redirect.PIPE);
        pb.redirectOutput(new File("out.txt"));
        Process proc = pb.start();

        float a = -1, b = 1;
        int n = 10;

        float[] xarr = new float[n];
        Random random = new Random();
        for (int i = 0; i < n; i++) {
            xarr[i] = random.nextFloat() * (b - a) + a;
        }
        System.out.println(Arrays.toString(xarr));

        DataOutputStream writer = new DataOutputStream(new BufferedOutputStream(proc.getOutputStream()));
        for (float x : xarr) {
            float f_std = (float) Math.pow(1 + x, 0.25);
            float f_my = calc(x);
            writer.writeFloat(x);
            writer.writeFloat(f_my);
            writer.writeFloat(f_std);
            writer.writeFloat(Math.abs(f_my - f_std));
            writer.flush();
        }
        writer.close();
        while (proc.isAlive());
    }

    private static float calc(float x) {
        float res = 1+x/4;
        float m_one_n = 1;
        float upper = 1;
        float four_n = 4;
        float fact_n = 1;
        float x_n = (float) Math.pow(x, 1);
        for (int n = 2;; ++n) {
            m_one_n *= -1;
            upper *= (4 * n - 5);
            four_n *= 4;
            fact_n *= n;
            x_n *= x;

            float cur = m_one_n * upper / (four_n * fact_n) * x_n;
            if (Math.abs(cur) < 1e-5)
                break;
            res += cur;
        }
        return res;
    }
}
