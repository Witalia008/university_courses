import sun.awt.windows.ThemeReader;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.nio.ByteBuffer;
import java.nio.channels.Channel;
import java.nio.channels.Channels;
import java.nio.channels.WritableByteChannel;
import java.util.Scanner;

/**
 * Created by witalia on 05.11.15.
 */
public class SubMain {
    public static final String PID;
    static {
        String name = ManagementFactory.getRuntimeMXBean().getName();
        PID = name.split("@")[0];
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        System.err.println("P1: Start");

        // P1 starts process P2
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(new File("/home/witalia/Dropbox/Projects/neww/target/classes/"));
        pb.command("/home/witalia/Java/jdk1.8.0_60/bin/java", "SubSubMain");
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.redirectError(ProcessBuilder.Redirect.INHERIT);
        System.err.println("Create process P2");
        Process proc = pb.start();


        // gets id of P2
        Scanner sc = new Scanner(System.in);
        while (!sc.hasNext()) { Thread.sleep(10); }
        String pid = sc.next();
        sc.close();
        System.err.println("P1: P2_id = " + pid);


        WritableByteChannel channel = Channels.newChannel(System.out);

        System.err.println("P1: Write part1 to K1");
        // Write part1 to a channel
        channel.write(ByteBuffer.wrap(Main.formatMsg(Integer.parseInt(PID), "Hello, ".getBytes())));

        // send signal to P2
        Main.sendSignal("SIGIO", pid);

        System.err.println("P1: Signal Sent to " + pid);

        // Wait until P2 wrote its data
        while (proc.isAlive()) {
            Thread.sleep(100);
        }

        // Write part2 to a channel
        System.err.println("P1: Write part2 to K1");
        channel.write(ByteBuffer.wrap(Main.formatMsg(Integer.parseInt(PID), "World!".getBytes())));

        System.err.println("P1: done");
    }
}
