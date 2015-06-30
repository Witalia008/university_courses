// This file contains the main() function for the Scheduling
// simulation.  Init() initializes most of the variables by
// reading from a provided file.  SchedulingAlgorithm.run() is
// called from main() to run the simulation.  Summary-Results
// is where the summary results are written, and Summary-Processes
// is where the process scheduling summary is written.

// Created by Alexander Reeder, 2001 January 06
package sched;

import java.io.*;
import java.util.Random;
import java.util.StringTokenizer;
import java.util.Vector;

public class Scheduling {

    private static int processNumber = 5;

    private static int time_average = 1000;
    private static int time_stddev = 200;

    private static int run_time_average = 200;
    private static int run_time_stddev = 100;

    private static int block_time_average = 100;
    private static int block_time_stddev = 30;

    private static int runtime = 1000;
    private static int quantum = 10;

    private static Vector processVector = new Vector();
    private static Results result = null;

    private static String logFile = "Summary-Processes";
    private static String resultsFile = "Summary-Results";

    private static void Init(File f) {
        String line;

        try {
            //BufferedReader in = new BufferedReader(new FileReader(f));
            DataInputStream in = new DataInputStream(new FileInputStream(f));
            while ((line = in.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(line);
                if (st.hasMoreTokens()) {
                    st.nextToken();
                }
                if (line.startsWith("numprocess")) {
                    processNumber = Common.s2i(st.nextToken());
                }
                if (line.startsWith("time_average")) {
                    time_average = Common.s2i(st.nextToken());
                }
                if (line.startsWith("time_stddev")) {
                    time_stddev = Common.s2i(st.nextToken());
                }
                if (line.startsWith("run_time_average")) {
                    run_time_average = Common.s2i(st.nextToken());
                }
                if (line.startsWith("run_time_stddev")) {
                    run_time_stddev = Common.s2i(st.nextToken());
                }
                if (line.startsWith("block_time_average")) {
                    block_time_average = Common.s2i(st.nextToken());
                }
                if (line.startsWith("block_time_stddev")) {
                    block_time_stddev = Common.s2i(st.nextToken());
                }
                if (line.startsWith("runtime")) {
                    runtime = Common.s2i(st.nextToken());
                }
                if (line.startsWith("quantum")) {
                    quantum = Common.s2i(st.nextToken());
                }
                if (line.startsWith("summary_file")) {
                    resultsFile = st.nextToken();
                }
                if (line.startsWith("log_file")) {
                    logFile = st.nextToken();
                }
            }
            in.close();
        } catch (IOException e) { /* Handle exceptions */ }
    }

    private static void debug() {
        int i = 0;

        System.out.println("processNumber " + processNumber);
        System.out.println("time_average " + time_average);
        System.out.println("time_stddev " + time_stddev);
        System.out.println("run_time_average " + run_time_average);
        System.out.println("run_time_stddev " + run_time_stddev);
        System.out.println("block_time_average " + block_time_average);
        System.out.println("block_time_stddev " + block_time_stddev);
        int size = processVector.size();
        for (i = 0; i < size; i++) {
            Process process = (Process) processVector.elementAt(i);
            System.out.println("process " + i + " " + process.toString());
        }
        System.out.println("summary_file " + resultsFile);
        System.out.println("log_file " + logFile);
        System.out.println("runtime " + runtime);
    }

    public static int getRandom(int average, int stddev) {
        return new Random().nextInt(stddev * 2) + average - stddev;
        /*double X = Common.R1();
        while (X == -1.0) {
            X = Common.R1();
        }
        X = X * stddev;
        return (int) X + average;*/
    }

    public static void main(String[] args) {
        int i = 0;

        if (args.length != 1) {
            System.out.println("Usage: 'java Scheduling <INIT FILE>'");
            System.exit(-1);
        }
        File f = new File(args[0]);
        if (!(f.exists())) {
            System.out.println("Scheduling: error, file '" + f.getName() + "' does not exist.");
            System.exit(-1);
        }
        if (!(f.canRead())) {
            System.out.println("Scheduling: error, read of " + f.getName() + " failed.");
            System.exit(-1);
        }
        System.out.println("Working...");
        Init(f);

        while (processVector.size() < processNumber) {
            int cputime_before_block = getRandom(run_time_average, run_time_stddev);
            int block_time = getRandom(block_time_average, block_time_stddev);
            int cputime = getRandom(time_average, time_stddev);

            processVector.addElement(new Process(cputime, cputime_before_block, block_time));
        }

        result = SchedulingAlgorithm.run(runtime, quantum, processVector, logFile);
        try {
            //BufferedWriter out = new BufferedWriter(new FileWriter(resultsFile));
            PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
            out.println(result);

            out.println("\nAverage runtime: " + time_average);
            out.println("Standard runtime average Deviation: " + time_stddev);
            out.println("\nAverage runtime before blocking: " + run_time_average);
            out.println("Standard runtime average Deviation: " + run_time_stddev);
            out.println("\nAverage of blocking time: " + block_time_average);
            out.println("Standard blocking time Deviation: " + block_time_stddev);
            out.println("\nProcess #\tT before block\tBlocking time\tCPU Completed\tCPU Blocked");
            for (i = 0; i < processVector.size(); i++) {
                Process process = (Process) processVector.elementAt(i);
                out.print(getTabString(i, ""));
                out.print(getTabString(process.cputime_before_block, " (ms)"));
                out.print(getTabString(process.blocking_time, " (ms)"));
                out.print(getTabString(process.cpudone, " (ms)"));
                out.println(process.numblocked + " times");
            }
            out.close();
        } catch (IOException e) { /* Handle exceptions */ }
        System.out.println("Completed.");
    }

    public static String getTabString(int x, String suf) {
        String res = "" + x + suf + "\t";
        if (x < 100) {
            res += "\t";
        }
        return res;
    }
}

