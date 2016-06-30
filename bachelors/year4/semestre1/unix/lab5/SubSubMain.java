import sun.misc.Signal;
import sun.misc.SignalHandler;

import java.io.*;
import java.lang.management.ManagementFactory;
import java.nio.ByteBuffer;
import java.nio.channels.Channel;
import java.nio.channels.Channels;
import java.nio.channels.WritableByteChannel;
import java.util.Arrays;
import java.util.Scanner;

/**
 * Created by witalia on 03.12.15.
 */
public class SubSubMain {

    public static final String PID;
    static {
        String name = ManagementFactory.getRuntimeMXBean().getName();
        PID = name.split("@")[0];
    }

    private static boolean canWrite = false;
    public static void main(String[] args) throws InterruptedException, IOException {
        // Send PID to P1
//        System.out.println(PID);
        System.err.println("P2: " + PID);
        System.err.println("P2: Start");

        // Setup signal handling
        SignalHandler handler = signal -> {
            System.err.println("P2: Signal");
            if (signal.getName().equals("IO")) {
                canWrite = true;
                System.err.println("P2: Signal received");
            }
        };
        Signal.handle(new Signal("IO"), handler);

        // Open file and calculate checksum
        System.err.println("P2: reading file");
        int sum = 0;
        BufferedInputStream inp = new BufferedInputStream(new FileInputStream(new File("/home/witalia/Dropbox/Projects/neww/out.txt")));
        while (inp.available() > 0) {
            sum = sum + inp.read();
        }
        System.err.println("P2: file read");

        // Wait for signal
        while (!canWrite) {
            Thread.sleep(10);
        }
        System.err.println("P2: Writing to K1");

        // Write checksum to a channel
        WritableByteChannel channel = Channels.newChannel(System.out);
        ByteBuffer bb = ByteBuffer.allocate(64);
        bb.putInt(Integer.parseInt(PID));
        bb.putInt(sum);
        bb.position(0);
        channel.write(bb);

        System.err.println("P2: done");
    }
}
