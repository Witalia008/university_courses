import sun.misc.Signal;
import sun.misc.SignalHandler;

import java.io.*;
import java.lang.management.ManagementFactory;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.nio.channels.WritableByteChannel;
import java.util.Arrays;

/**
 * Created by witalia on 17.09.15.
 */

public class Main {

    public static void sendSignal(String sigName, String procID) throws IOException {
        Runtime.getRuntime().exec(String.format("kill -s %s %s", sigName, procID));
    }

    public static final String PID;
    static {
        String name = ManagementFactory.getRuntimeMXBean().getName();
        PID = name.split("@")[0];
    }

    public static byte[] formatMsg(Integer pid, byte[] msg) {
        ByteBuffer bb = ByteBuffer.allocate(64);
        bb.putInt(pid);
        bb.put(msg);
        bb.position(0);
        return bb.array();
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        System.err.println("Start");

        System.err.println("Create channel K1");
        new PrintWriter(new File("chan")).close();

        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(new File("/home/witalia/Dropbox/Projects/neww/target/classes/"));
        pb.command("/home/witalia/Java/jdk1.8.0_60/bin/java", "SubMain");
        pb.redirectInput(ProcessBuilder.Redirect.INHERIT);
        pb.redirectOutput(ProcessBuilder.Redirect.PIPE);
        pb.redirectError(ProcessBuilder.Redirect.INHERIT);
        System.err.println("Create process P1");
        Process proc = pb.start();

        BufferedInputStream inp = new BufferedInputStream(proc.getInputStream());
        while (proc.isAlive() || inp.available() > 0) {
            if (inp.available() > 0) {
                byte[] buf = new byte[64];
                int bytesRead = inp.read(buf, 0, 64);
                if (bytesRead != -1) {
                    ByteBuffer bb = ByteBuffer.wrap(buf);
                    Integer pid = bb.getInt(0);
                    byte[] rest = Arrays.copyOfRange(buf, 4, 64);
                    System.out.println(pid + ": " + Arrays.toString(buf));
                    System.out.println(pid + ": " + new String(rest));
                }
            }
            Thread.sleep(100);
        }
    }
}
