import java.io.*;
import java.util.*;

/**
 * Created by Witalia on 9/30/2014.
 */
public class Main {
    private static int res = Integer.MAX_VALUE;
    private static int[] ress = null;
    private static Process[] procs = null;

    private static int getResult(Process p) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        return Integer.parseInt(reader.readLine());
    }
    private static int hasResult(Process[] procs) throws IOException {
        if (res != Integer.MAX_VALUE)
            return res;
        boolean canAnswer = true;
        for (int i = 0; i < procs.length; ++i) {
            Process p = procs[i];
            if (p.isAlive() == false && ress[i] == Integer.MAX_VALUE && p.exitValue() == 0)
                ress[i] = getResult(p);
            if (ress[i] == Integer.MAX_VALUE)
                canAnswer = false;
        }
        res = 1;
        for (int i = 0; i < ress.length; ++i) {
            res = res * ress[i];
            canAnswer |= (ress[i] == 0);
        }
        if (canAnswer == false)
            res = Integer.MAX_VALUE;
        return res;
    }
    private static void terminate(Process[] procs) {
        for (Process p : procs)
            if (p.isAlive())
                p.destroyForcibly();
    }
    private static boolean hasAlive(Process[] procs) {
        for (Process p : procs)
            if (p.isAlive())
                return true;
        return false;
    }
    private static Process runSimpleProcess(ProcessBuilder pb, String t, String r) throws IOException {
        pb.command("java", "Func", t, r);
        return pb.start();
    }
    public static void main(String[] args) throws IOException, InterruptedException {
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(new File("D:\\Projects\\Intellij\\OSLab1\\out\\production\\OSLab1\\"));
        pb.redirectOutput(ProcessBuilder.Redirect.PIPE);

        procs = new Process[]{
                runSimpleProcess(pb, "-1", "3"),
                runSimpleProcess(pb, "2000", "1")};
        ress = new int[procs.length];
        Arrays.fill(ress, Integer.MAX_VALUE);

        BufferedReader usrInput = new BufferedReader(new InputStreamReader(System.in));
        boolean needPrompt = true;
        long prevPt = System.currentTimeMillis();
        while (hasAlive(procs)) {
            //Thread.sleep(100);
            if (usrInput.ready()) {
                int ascii = usrInput.read();
                System.out.println("ASCII: " + ascii);
                if (ascii == 'q') {
                    terminate(procs);
                    break;
                }
            }
            res = hasResult(procs);
            if (res != Integer.MAX_VALUE) {
                terminate(procs);
                break;
            }

            if (needPrompt && System.currentTimeMillis() - prevPt > 5000) {
                System.out.println("0. Terminate\n" +
                        "1. Continue\n" +
                        "2. Continue without prompt\n");
                String req = usrInput.readLine();
                switch (req) {
                    case "0":
                        terminate(procs);
                        break;

                    case "1":
                        break;

                    case "2":
                        needPrompt = false;
                        break;

                    default:
                        continue;
                }
                prevPt = System.currentTimeMillis();
            }
        }
        res = hasResult(procs);
        if (res != Integer.MAX_VALUE) {
            System.out.println("Calculated value: " + res);
        }
    }
}
