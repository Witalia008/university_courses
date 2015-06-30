import java.io.File;

/**
 * Created by Witalia on 02.12.2014.
 */
public class Letter {
    private String from = "";
    private String to = "";
    private String subject = "";
    private String text = "";
    private File[] attachments = new File[0];

    public Letter() {
    }

    public Letter(String from, String to, String subject, String text, File[] attachments) {
        this.from = from;
        this.to = to;
        this.subject = subject;
        this.text = text;
        this.attachments = attachments;
    }

    public String getFrom() {
        return from;
    }

    public String getTo() {
        return to;
    }

    public String getSubject() {
        return subject;
    }

    public String getText() {
        return text;
    }

    public File[] getAttachments() {
        return attachments;
    }


    public void setFrom(String from) {
        this.from = from;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public void setSubject(String subject) {
        this.subject = subject;
    }

    public void setText(String text) {
        this.text = text;
    }

    public void setAttachments(File[] attachments) {
        this.attachments = attachments;
    }

    public void addFrom(String from) {
        if (this.from.equals("") == false) {
            this.from += ",";
        }
        this.from += from;
    }

    public void addTo(String to) {
        if (this.to.equals("") == false) {
            this.to += ",";
        }
        this.to += to;
    }

    public void addText(String text) {
        this.text += text;
    }
}
