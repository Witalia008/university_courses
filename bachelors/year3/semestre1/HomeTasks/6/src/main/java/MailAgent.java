import org.apache.commons.io.IOUtils;

import javax.activation.DataHandler;
import javax.activation.DataSource;
import javax.activation.FileDataSource;
import javax.mail.*;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

/**
 * Created by Witalia on 02.12.2014.
 */
public class MailAgent {
    private static String imapHost = "imap";
    private static String imapPort = "993";
    private static String smtpHost = "smtp";
    private static String smtpPort = "587";

    private static boolean authRequired;
    private static String username;
    private static String password;

    public static void setCredentials(String username, String password) {
        if (username == null || password == null) {
            authRequired = false;
        } else {
            authRequired = true;
            MailAgent.username = username;
            MailAgent.password = password;
        }
    }

    public static void setImapServer(String imapHost, String imapPort) {
        if (imapHost != null) {
            MailAgent.imapHost = imapHost;
        }
        if (imapPort != null) {
            MailAgent.imapPort = imapPort;
        }
    }

    public static void setSmtpServer(String smtpHost, String smtpPort) {
        if (smtpHost != null) {
            MailAgent.smtpHost = smtpHost;
        }
        if (smtpPort != null) {
            MailAgent.smtpPort = smtpPort;
        }
    }

    public static String send(Letter mail) {
        Properties properties = System.getProperties();
        properties.setProperty("mail.smtp.host", smtpHost);
        properties.setProperty("mail.smtp.port", smtpPort);
        properties.setProperty("mail.smtp.starttls.enable", "true");
        properties.setProperty("mail.smtp.auth", "true");

        Session session = Session.getDefaultInstance(properties,
                new Authenticator() {
                    @Override
                    protected PasswordAuthentication getPasswordAuthentication() {
                        return new PasswordAuthentication(username, password);
                    }
                });

        try {
            MimeMessage message = new MimeMessage(session);
            message.setFrom(new InternetAddress(mail.getFrom()));

            message.addRecipients(Message.RecipientType.TO,
                    InternetAddress.parse(mail.getTo()));

            message.setSubject(mail.getSubject());

            BodyPart messageBodyPart = new MimeBodyPart();
            messageBodyPart.setText(mail.getText());

            Multipart multipart = new MimeMultipart();
            multipart.addBodyPart(messageBodyPart);

            for (File file : mail.getAttachments()) {
                messageBodyPart = new MimeBodyPart();
                DataSource source = new FileDataSource(file);
                messageBodyPart.setDataHandler(new DataHandler(source));
                messageBodyPart.setFileName(file.getName());
                multipart.addBodyPart(messageBodyPart);
            }

            message.setContent(multipart);

            Transport.send(message);
        } catch (MessagingException e) {
            return e.getMessage();
        }

        return "success";
    }

    public static String[] getFolders() {
        Properties properties = new Properties();//System.getProperties();
        properties.setProperty("mail.store.protocol", "imaps");

        Session session = Session.getInstance(properties, null);
        try {
            Store store = session.getStore();
            store.connect(imapHost, username, password);

            Folder[] folders = store.getDefaultFolder().list();
            String[] names = new String[folders.length];
            for (int i = 0; i < names.length; i++) {
                names[i] = folders[i].getFullName();
            }
            return names;
        } catch (MessagingException e) {
            e.printStackTrace();
            return new String[0];
        }
    }

    public static Letter[] getFolderContent(String folderName, int maxLetters) {
        Properties properties = new Properties();//System.getProperties();
        properties.setProperty("mail.store.protocol", "imaps");

        Session session = Session.getInstance(properties, null);
        try {
            Store store = session.getStore();
            store.connect(imapHost,    username, password);

            Folder folder = store.getFolder(folderName);
            folder.open(Folder.READ_ONLY);

            Letter[] res = new Letter[Math.min(maxLetters, folder.getMessageCount())];

            for (int i = 0; i < res.length; i++) {
                Message msg = folder.getMessage(folder.getMessageCount() - i);

                res[i] = new Letter();

                for (Address from : msg.getFrom()) {
                    res[i].addFrom(from.toString());
                }
                for (Address to : msg.getRecipients(Message.RecipientType.TO)) {
                    res[i].addTo(to.toString());
                }
                res[i].setSubject(msg.getSubject());

                Object content = msg.getContent();
                if (content instanceof String) {
                    res[i].setText((String) content);
                } else if (content instanceof Multipart) {
                    List<File> attachments = new ArrayList<>();
                    Multipart multipart = (Multipart) content;
                    for (int j = 0; j < multipart.getCount(); ++j) {
                        BodyPart bodyPart = multipart.getBodyPart(j);
                        if (Part.ATTACHMENT.equalsIgnoreCase(bodyPart.getDisposition())) {
                            if (!bodyPart.getFileName().equals("")) {
                                String fld = System.getProperty("user.home") + "\\MyMail\\"
                                        + username + "\\" + folderName;
                                new File(fld).mkdirs();
                                File file = new File(fld + "\\" + bodyPart.getFileName());
                                if (!file.exists()) {
                                    file.createNewFile();
                                }
                                IOUtils.copy(bodyPart.getInputStream(),
                                        new FileOutputStream(file));
                                attachments.add(file);
                            }
                        } else {
                            Object bodyContent = bodyPart.getContent();
                            if (bodyContent instanceof String) {
                                res[i].addText(((String) bodyContent));
                            } else if (bodyContent instanceof MimeMultipart) {
                                MimeMultipart mimeMultipart = (MimeMultipart) bodyContent;
                                for (int k = 0; k < mimeMultipart.getCount(); ++k) {
                                    res[i].addText(mimeMultipart.getBodyPart(k).getContent().toString());
                                }
                            }
                        }
                    }
                    res[i].setAttachments(attachments.toArray(new File[attachments.size()]));
                }
                res[i].addText("\nsent on " + msg.getSentDate());
            }

            return res;
        } catch (MessagingException | IOException e) {
            e.printStackTrace();
            return new Letter[0];
        }
    }
}
