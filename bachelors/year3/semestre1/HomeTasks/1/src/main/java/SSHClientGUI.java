import javax.swing.*;
import javax.swing.text.AbstractDocument;
import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.DocumentFilter;
import java.applet.Applet;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.*;
import java.util.Date;

/**
 * Created by Witalia on 29.10.2014.
 */
public class SSHClientGUI extends Applet {
    private SSHManager sshManager;
    private JTextArea terminal;
    private DocumentSizeFilter filter = new DocumentSizeFilter();

    class DocumentSizeFilter extends DocumentFilter {
        private int minSymbolsCount = 0;
        private int allSymbolsCount = 0;
        private boolean inputBlocked = false;

        public int getMinSymbolsCount() {
            return minSymbolsCount;
        }

        public int getAllSymbolsCount() {
            return allSymbolsCount;
        }

        public void setInputBlocked(boolean inputBlocked) {
            this.inputBlocked = inputBlocked;
        }

        @Override
        public void remove(FilterBypass fb, int offset, int length)
                throws BadLocationException {
            if (offset >= minSymbolsCount) {

                super.remove(fb, offset, length);
                allSymbolsCount -= length;
            }
        }

        @Override
        public void replace(FilterBypass fb, int offset, int length,
                            String text, AttributeSet attrs)
                throws BadLocationException {
            if (offset >= minSymbolsCount && inputBlocked == false) {
                super.replace(fb, offset, length, text, attrs);
                allSymbolsCount += text.length() - length;
            }
        }

        @Override
        public void insertString(FilterBypass fb, int offset,
                                 String string, AttributeSet attr)
                throws BadLocationException {
            if (offset >= minSymbolsCount && inputBlocked == false) {
                super.insertString(fb, offset, string, attr);
                allSymbolsCount += string.length();
            }
        }

        public void updateMin() {
            minSymbolsCount = allSymbolsCount;
        }
    }

    public SSHClientGUI() {
        setLayout(new BorderLayout());

        terminal = new JTextArea();

        ((AbstractDocument)terminal.getDocument())
                .setDocumentFilter(filter);

        configureInputHandler();

        add(new JScrollPane(terminal), BorderLayout.CENTER);

        setVisible(true);

        doConnectionRoutine();
    }

    private void appendToTerminal(String text) {
        terminal.append(text);
        filter.updateMin();
        terminal.setCaretPosition(filter.getAllSymbolsCount());
    }

    private void configureInputHandler() {
        terminal.addKeyListener(new KeyListener() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.isControlDown() && e.getKeyCode() == KeyEvent.VK_C) {
                    filter.setInputBlocked(false);
                    terminal.append("Ctrl+C\n");
                    sshManager.interruptCommand();
                }
                if (e.getKeyCode() == KeyEvent.VK_ENTER && sshManager != null) {
                    if (sshManager.isCommandRunning() == true) {
                        return;
                    }
                    String command = terminal.getText().substring(
                        filter.getMinSymbolsCount(),
                        filter.getAllSymbolsCount()
                    );

                    PipedInputStream pipedInputStream = new PipedInputStream();
                    PipedOutputStream pipedOutputStream = new PipedOutputStream();
                    try {
                        pipedOutputStream.connect(pipedInputStream);
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                    new Thread() {
                        @Override
                        public void run() {
                            BufferedReader in = new BufferedReader(
                                    new InputStreamReader(pipedInputStream)
                            );
                            try {
                                sleep(100);
                                filter.setInputBlocked(true);
                                String inputLine;
                                while ((inputLine = in.readLine()) != null) {
                                    filter.setInputBlocked(false);
                                    appendToTerminal(inputLine + "\n");
                                    filter.setInputBlocked(true);
                                }
                                in.close();
                                filter.setInputBlocked(false);
                                appendToTerminal(sshManager.getFullName() + " $ ");
                            } catch (IOException | InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                    }.start();
                    sshManager.sendCommand(command, pipedOutputStream);
                }
            }

            @Override
            public void keyTyped(KeyEvent e) {
            }

            @Override
            public void keyReleased(KeyEvent e) {
            }
        });
    }

    private void doConnectionRoutine() {
        JTextField userName = new JTextField("Witalia");
        JTextField hostName = new JTextField("127.0.0.1");
        JPasswordField password = new JPasswordField();

        JPanel panel = new JPanel(new GridLayout(6, 1));
        panel.add(new JLabel("User name: "));
        panel.add(userName);
        panel.add(new JLabel("Host: "));
        panel.add(hostName);
        panel.add(new JLabel("Password: "));
        panel.add(password);
        userName.grabFocus();

        int result = JOptionPane.showConfirmDialog(this, panel, "Enter host data",
                JOptionPane.OK_CANCEL_OPTION);
        if (result == JOptionPane.OK_OPTION) {
            setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

            sshManager = new SSHManager(
                    userName.getText(), hostName.getText(),
                    new String(password.getPassword()), null
            );
            if (sshManager.connect() != null) {
                JOptionPane.showMessageDialog(this, "Can't connect", "Error",
                        JOptionPane.ERROR_MESSAGE);
            } else {
                appendToTerminal(
                        "Connection successful.\n"
                                + new Date().toString() + "\n"
                                + sshManager.getFullName() + " $ "
                );
            }
            setCursor(Cursor.getDefaultCursor());
        }
    }
}
