import javax.swing.*;
import java.awt.*;
import java.awt.List;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.IOException;
import java.util.*;

/**
 * Created by Witalia on 02.12.2014.
 */
public class LetterView extends JFrame {
    enum ViewType {
        SEND, SHOW
    }

    private JTextField from = new JTextField();
    private JTextField to = new JTextField();
    private JTextField subject = new JTextField();
    private JTextPane text = new JTextPane();
    {
        text.setContentType("text/html");
    }
    private List attachments = new List();
    private java.util.List<File> files = new ArrayList<>();

    public void setTo(String to) {
        this.to.setText(to);
    }

    public void setFrom(String from) {
        this.from.setText(from);
    }

    public LetterView(ViewType type, Letter mail) {
        this(type);
        this.from.setText(mail.getFrom());
        this.to.setText(mail.getTo());
        this.subject.setText(mail.getSubject());
        this.text.setText("<html>" + mail.getText() + "</html>");
        files = Arrays.asList(mail.getAttachments());
        for (File file : mail.getAttachments()) {
            this.attachments.add(file.getAbsolutePath());
        }
    }

    public LetterView(ViewType type) {
        super(type.toString() + " email");
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        setPreferredSize(new Dimension(700, 500));
        setLayout(new BorderLayout());

        from.setEditable(false);
        if (type == ViewType.SHOW) {
            to.setEditable(false);
            subject.setEditable(false);
            text.setEditable(false);
        }

        JPanel upper = new JPanel(new GridLayout(3, 2));
        upper.add(new JLabel("FROM: "));
        upper.add(from);
        upper.add(new JLabel("TO: "));
        upper.add(to);
        upper.add(new JLabel("SUBJECT: "));
        upper.add(subject);

        JButton btnSend = new JButton("Send");
        JButton btnAttach = new JButton("Attach");
        JButton btnRemove = new JButton("Remove Attachment");
        JButton btnCancel = new JButton("Cancel");
        JPanel buttons = new JPanel();
        buttons.add(btnSend);
        buttons.add(btnAttach);
        buttons.add(btnRemove);
        buttons.add(btnCancel);

        JPanel bottom = new JPanel(new BorderLayout());
        if (type == ViewType.SEND) {
            bottom.add(buttons, BorderLayout.SOUTH);
        }
        bottom.add(new JScrollPane(attachments), BorderLayout.CENTER);

        add(upper, BorderLayout.NORTH);
        add(bottom, BorderLayout.SOUTH);
        add(new JScrollPane(text), BorderLayout.CENTER);

        pack();
        setVisible(true);

        btnAttach.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser();
            if (chooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
                attachments.add(chooser.getSelectedFile().getAbsolutePath());
                files.add(chooser.getSelectedFile());
            }
        });
        btnRemove.addActionListener(e -> {
            int[] selected = attachments.getSelectedIndexes();
            Arrays.sort(selected);
            for (int i = selected.length - 1; i >= 0; i--) {
                attachments.remove(selected[i]);
                files.remove(selected[i]);
            }
        });
        btnSend.addActionListener(e -> {
            setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
            JOptionPane.showMessageDialog(null,
                    "Sending result: " +
                            MailAgent.send(new Letter(
                                    from.getText(), to.getText(),
                                    subject.getText(), text.getText(),
                                    files.toArray(new File[files.size()])))
            );
            setCursor(Cursor.getDefaultCursor());
            dispose();
        });
        btnCancel.addActionListener(e -> dispose());
        attachments.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    String fileName = attachments.getSelectedItem();
                    try {
                        new ProcessBuilder("explorer.exe", "/select," + fileName + "").start();
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                }
            }
        });
    }
}
