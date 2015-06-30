// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the run() function.
package sched;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Vector;

public class SchedulingAlgorithm {
    public static Results run(int runtime, int quantum, Vector processVector, String resultsFile) {
        int comptime = 0;
        int currentProcess = -1;
        int completed = 0;

        Results result = new Results("Interactive", "Round-robin", 0);
        PrintStream out = null;
        try {
            //BufferedWriter out = new BufferedWriter(new FileWriter(resultsFile));
            //OutputStream out = new FileOutputStream(resultsFile);
            out = new PrintStream(new FileOutputStream(resultsFile));
            Process process = null;
            while (comptime < runtime) {
                currentProcess = getNextProcess(comptime, currentProcess, processVector);
                comptime += quantum;

                if (currentProcess != -1) {
                    process = (Process) processVector.elementAt(currentProcess);
                    processLog(comptime, currentProcess, process, out, "registered");
                    process.cpudone += quantum;

                    if (process.isDone()) {
                        completed++;
                        processLog(comptime, currentProcess, process, out, "completed");
                        if (completed == processVector.size()) {
                            return result;
                        }
                    }
                    if (process.needsBlocking(comptime)) {
                        processLog(comptime, currentProcess, process, out, "I/O blocked");
                        process.numblocked++;
                        process.last_blocked = comptime;
                        process.last_blocked_local = process.cpudone;
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        finally {
            if (out != null) {
                out.close();
            }
            result.compuTime = comptime;
        }
        return result;
    }

    private static int getNextProcess(int comptime, int currentProcess, Vector processVector) {
        Process process;
        for (int i = 0; i < processVector.size(); ++i) {
            currentProcess = (currentProcess + 1) % processVector.size();
            process = ((Process) processVector.elementAt(currentProcess));
            if (!(process.isDone() || process.isBlocked(comptime))) {
                return currentProcess;
            }
        }
        return -1;
    }

    private static void processLog(int comptime, int currentProcess, Process process, PrintStream out, String message) {
        out.println(comptime + "\t Process: " + currentProcess + " " + message + "... (" + process.cputime_before_block + " " + process.blocking_time + " " + process.cpudone + ")");
    }
}
