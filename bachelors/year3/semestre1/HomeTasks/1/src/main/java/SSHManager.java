import com.jcraft.jsch.*;

import java.io.*;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Created by Witalia on 29.10.2014.
 */
public class SSHManager {
    private static final Logger LOGGER =
            Logger.getLogger(SSHManager.class.getName());
    private JSch sshChannel;
    private String userName;
    private String hostName;
    private int connectionPort;
    private String password;
    private Session connection;
    private int timeOut;
    private boolean isInsecure;
    private Thread commandThread;
    private ChannelExec channel;

    public boolean isCommandRunning() {
        return commandThread != null && commandThread.isAlive();
    }

    public void interruptCommand() {
        if (commandThread != null) {
            commandThread.interrupt();
            channel.disconnect();
        }
    }

    public String getCommandResult() {
        if (commandThread == null) {
            return null;
        }
        try {
            commandThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return commandThread.toString();
    }

    public String getFullName() {
        return userName + "@" + hostName;
    }

    public SSHManager(String userName, String hostName, String password,
                      String knownHostsFileName) {
        sshChannel = new JSch();

        if (knownHostsFileName != null) {
            try {
                sshChannel.setKnownHosts(knownHostsFileName);
            } catch (JSchException e) {
                log(Level.SEVERE, e.getMessage());
            }
        }

        this.userName = userName;
        this.hostName = hostName;
        this.password = password;

        this.connectionPort = 22;
        this.timeOut = 60_000;
        this.isInsecure = knownHostsFileName == null;
    }

    public SSHManager(String userName, String hostName, String password,
                      String knownHostsFileName, int connectionPort) {
        this(userName, hostName, password, knownHostsFileName);
        this.connectionPort = connectionPort;
    }

    public SSHManager(String userName, String hostName, String password,
                      String knownHostsFileName, int connectionPort, int timeOut) {
        this(userName, hostName, password, knownHostsFileName, connectionPort);
        this.timeOut = timeOut;
    }

    public String connect() {
        String errorMessage = null;

        try {
            connection = sshChannel.getSession(userName, hostName, connectionPort);
            connection.setPassword(password);

            if (isInsecure) {
                Properties config = new Properties();
                config.put("StrictHostKeyChecking", "no");
                connection.setConfig(config);
            }

            connection.connect(timeOut);
        } catch (JSchException e) {
            errorMessage = e.getMessage();
            log(Level.WARNING, errorMessage);
        }

        return errorMessage;
    }

    public void sendCommand(String command, OutputStream outputStream) {
        commandThread = new Thread() {
            private StringBuffer result = new StringBuffer();
            private boolean wasInterrupted = false;

            @Override
            public String toString() {
                return result.toString();
            }

            @Override
            public void run() {
                try {
                    channel = (ChannelExec) connection.openChannel("exec");
                    channel.setCommand(command);
                    channel.connect();
                    BufferedReader in = new BufferedReader(
                            new InputStreamReader(channel.getInputStream())
                    );
                    String inputLine;
                    PrintWriter out = null;
                    if (outputStream != null) {
                        out = new PrintWriter(outputStream);
                    }
                    while ((inputLine = in.readLine()) != null) {
                        if (wasInterrupted == true) {
                            break;
                        }
                        result.append(inputLine + "\n");
                        if (out != null) {
                            out.println(inputLine);
                            out.flush();
                        }
                    }
                    out.close();
                    in.close();
                    channel.disconnect();
                } catch (JSchException | IOException e) {
                    log(Level.WARNING, e.getMessage());
                }
            }

            @Override
            public void interrupt() {
                wasInterrupted = true;
            }
        };
        commandThread.start();
    }

    public void close() {
        connection.disconnect();
    }

    private void log(Level level, String message) {
        LOGGER.log(level, "{0}:{1} - {2}",
                new Object[]{hostName, connectionPort, message});
    }
}
