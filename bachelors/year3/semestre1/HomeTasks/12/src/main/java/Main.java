/**
 * Created by Witalia on 04.11.2014.
 */
public class Main {
    private Thread shower;

    public void stop() {
        if (shower != null) {
            shower.interrupt();
        }
    }

    public void showHierarchy(final ThreadGroup group) {
        shower = new Thread() {
            private ThreadGroup g = group;
            boolean interrupted = false;
            @Override
            public void run() {
                while (!isInterrupted()) {
                    System.out.println("UPDATE: ");
                    showStructure(group, 0);
                    try {
                        sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }

            private void showStructure(ThreadGroup group, int level) {
                System.out.println(tabs(level));
                System.out.println(tabs(level) + "Group name: " + group.getName());

                System.out.println(tabs(level) + "Inside Threads:");
                Thread[] listThreads = new Thread[group.activeCount()];
                int count = group.enumerate(listThreads, false);
                for (int i = 0; i < count; ++i) {
                    System.out.println(tabs(level + 1) + listThreads[i].getName());
                }

                System.out.println(tabs(level) + "Inside Groups:");
                ThreadGroup[] listGroups = new ThreadGroup[group.activeGroupCount()];
                count = group.enumerate(listGroups, false);
                for (int i = 0; i < count; ++i) {
                    showStructure(listGroups[i], level + 1);
                }
            }

            private String tabs(int level) {
                String res = "";
                while (level-- > 0) {
                    res += "    ";
                }
                return res;
            }

            @Override
            public void interrupt() {
                interrupted = true;
            }

            @Override
            public boolean isInterrupted() {
                return interrupted;
            }
        };
        shower.start();
    }
}
