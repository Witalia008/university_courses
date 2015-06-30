package sched;

public class Process {
    public int runtime;
    public int cputime_before_block;
    public int blocking_time;
    public int cpudone;
    public int last_blocked;
    public int last_blocked_local;
    public int numblocked;

    public Process(int runtime, int cputime_before_block, int blocking_time) {
        this.runtime = runtime;
        this.cputime_before_block = cputime_before_block;
        this.blocking_time = blocking_time;
        last_blocked = -blocking_time;
    }

    public boolean isDone() {
        return cpudone >= runtime;
    }

    public boolean isBlocked(int cputime) {
        return last_blocked + blocking_time > cputime;
    }

    public boolean needsBlocking(int cputime) {
        return !isDone() && !isBlocked(cputime)
                && last_blocked_local + blocking_time + cputime_before_block <= cpudone;
    }

    @Override
    public String toString() {
        return "(cputime_before_block = " + cputime_before_block
                + ", blocking_time = " + blocking_time
                + ", cpudone = " + cpudone
                + ", last_blocked = " + last_blocked
                + ", numblocked = " + last_blocked + ")";
    }
}
