import org.junit.Test;

import java.util.Random;

/**
 * Created by Witalia on 04.11.2014.
 */
public class TestViewer {
    @Test
    public void testViewer() throws Exception {
        Main m = new Main();

        Random random = new Random();

        ThreadGroup[] groups = new ThreadGroup[5];
        for (int i = 0; i < groups.length; i++) {
            if (i == 0) {
                groups[i] = new ThreadGroup("Group" + i);
            } else {
                groups[i] = new ThreadGroup(groups[(i - 1) / 2], "Group" + i);
            }
        }

        Thread[] threads = new Thread[16];
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new MyThread(groups[((int) Math.ceil(Math.sqrt(((double) i))))],
                    "Thread" + i, random.nextInt(1000));
        }

        for (Thread i : threads) {
            i.start();
        }

        m.showHierarchy(groups[0]);

        for (Thread i : threads) {
            i.join();
        }
    }
}

class MyThread extends Thread {
    private int runningTime;

    MyThread(ThreadGroup group, String name, int runningTime) {
        super(group, name);
        this.runningTime = runningTime;
    }

    @Override
    public void run() {
        try {
            sleep(runningTime);
            System.out.println(getName() + " finished in "
                    + runningTime + " ms.");
        } catch (InterruptedException e) {
            System.out.println(getName() + " was interrupted.");
        }
    }
}
