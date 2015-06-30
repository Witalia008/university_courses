import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

/**
 * Created by Witalia on 30.10.2014.
 */
public class Main extends JFrame {
    private JList emails;
    private JList folders;
    private EmailListModel emailsModel = new EmailListModel();

    public Main() throws HeadlessException {
        super("Mail Client");
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(700, 500));

        MailAgent.setCredentials("username", "password");
        MailAgent.setSmtpServer("smtp.gmail.com", null);
        MailAgent.setImapServer("imap.gmail.com", null);

        JButton btnNewEmail = new JButton("New E-mail");
        JPanel buttons = new JPanel();
        buttons.add(btnNewEmail);

        add(buttons, BorderLayout.SOUTH);
        folders = new JList<>(MailAgent.getFolders());
        add(new JScrollPane(folders), BorderLayout.WEST);

        emails = new JList(emailsModel);
        add(new JScrollPane(emails), BorderLayout.CENTER);

        pack();
        setVisible(true);

        btnNewEmail.addActionListener(e ->
                new LetterView(LetterView.ViewType.SEND)
                        .setFrom("username@gmail.com"));
        folders.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    emailsModel.setLetters(MailAgent.getFolderContent(
                            (String) folders.getSelectedValue(), 5));
                }
            }
        });
        emails.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    new LetterView(LetterView.ViewType.SHOW,
                            emailsModel.getLetters()[emails.getSelectedIndex()]);
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Main());
    }
}

class EmailListModel extends AbstractListModel {
    private Letter[] letters;

    public EmailListModel() {
        letters = new Letter[0];
    }

    public void setLetters(Letter[] letters) {
        this.letters = letters;
        fireContentsChanged(this, 0, letters.length - 1);
    }

    public Letter[] getLetters() {
        return letters;
    }

    @Override
    public int getSize() {
        return letters.length;
    }

    @Override
    public Object getElementAt(int index) {
        return "<HTML>"
                + "<H1>" + letters[index].getFrom() + "</H1>"
                + "<H3>" + letters[index].getSubject() + "</H3>"
                + "<H5>" + letters[index].getText().substring(0,
                        Math.min(50, letters[index].getText().length())) + "</H5>"
                + "</HTML>";
    }
};