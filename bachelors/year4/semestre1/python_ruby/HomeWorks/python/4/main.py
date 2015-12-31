import os
import smtplib
from os.path import basename
from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.utils import COMMASPACE, formatdate
from email.header import decode_header
import imaplib
import email
import datetime
import sys
from builtins import print

my_email = 'username@ukr.net'
my_password = ''
smtp_server = 'smtp.ukr.net'
smtp_port = 465
imap_server = 'imap.ukr.net'
imap_port = 993
mail_folder = 'mail'


def send_mail(send_from, send_to, subject, text, files=None):
    assert isinstance(send_to, list)

    msg = MIMEMultipart(
        Date=formatdate(localtime=True)
    )
    msg['From'] = send_from
    msg['To'] = COMMASPACE.join(send_to)
    msg['Subject'] = subject
    msg.attach(MIMEText(text))

    for f in files or []:
        with open(f, "rb") as fil:
            msg.attach(MIMEApplication(
                fil.read(),
                Content_Disposition='attachment; filename="%s"' % basename(f),
                Name=basename(f)
            ))

    smtp = smtplib.SMTP_SSL(smtp_server, smtp_port)
    smtp.login(my_email, my_password)
    smtp.sendmail(send_from, send_to, msg.as_string())
    smtp.close()


def retrieve_mails(from_date):
    imap = imaplib.IMAP4_SSL(imap_server)
    imap.login(my_email, my_password)

    imap.select('inbox')
    date = from_date.strftime('%d-%b-%Y')
    result, data = imap.uid('search', None, '(SENTSINCE {date})'.format(date=date))
    for email_uid in reversed(data[0].split()):
        result, data = imap.uid('fetch', email_uid, '(RFC822)')
        raw_email = data[0][1]
        yield (email_uid, email.message_from_bytes(raw_email))

    imap.close()
    imap.logout()


# send_mail(my_email, [my_email], 'Test mail', 'Hello, World!', ['main.py'])
# inbox = list(retrieve_mails(datetime.date.today() - datetime.timedelta(3)))


from PySide.QtCore import *
from PySide.QtGui import *
from PySide.QtWebKit import *

qt_app = QApplication(sys.argv)


class FileWindow(QWidget):
    def __init__(self, parent=None, files=None):
        QWidget.__init__(self, parent)

        self.layout = QVBoxLayout()
        self.setWindowTitle('hehe')
        self.setMinimumWidth(800)

        self.layout.addWidget(QLabel('Attachments list:', self))

        self.files_list = QListWidget(self)
        if files is not None:
            self.set_files(files)
        self.files_list.itemDoubleClicked.connect(self.show_file_location)
        self.layout.addWidget(self.files_list)

        if files is None:
            print('aha')
            self.button_box = QHBoxLayout()
            self.delete_button = QPushButton('&Delete', self)
            self.delete_button.clicked.connect(self.delete_clicked)
            self.add_button = QPushButton('&Add', self)
            self.add_button.clicked.connect(self.add_clicked)

            self.button_box.addStretch(1)
            self.button_box.addWidget(self.delete_button)
            self.button_box.addWidget(self.add_button)

            self.layout.addLayout(self.button_box)

        self.setLayout(self.layout)

    @Slot(QListWidgetItem)
    def show_file_location(self, item):
        import subprocess
        subprocess.Popen(r'explorer /select,"%s"' % item.text().replace('/', '\\'))

    @Slot()
    def delete_clicked(self):
        item = self.files_list.currentItem()
        if item:
            self.files_list.takeItem(self.files_list.row(item))
        self.get_files()

    @Slot()
    def add_clicked(self):
        dialog = QFileDialog(self)
        dialog.setFileMode(QFileDialog.AnyFile)
        dialog.setViewMode(QFileDialog.Detail)
        if dialog.exec_():
            self.files_list.addItems(dialog.selectedFiles())

    def get_files(self):
        for i in range(0, self.files_list.count()):
            yield self.files_list.item(i).text()

    def set_files(self, files):
        self.files_list.clear()
        self.files_list.addItems(files)

    def run(self):
        self.show()
        qt_app.exec_()


class SendEmailWindow(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        self.setMinimumWidth(400)
        self.setWindowTitle('Send Email')

        self.layout = QVBoxLayout()

        self.form_layout = QFormLayout()

        self.from_label = QLabel(my_email, self)
        self.form_layout.addRow('From: ', self.from_label)

        self.to_field = QLineEdit(self)
        self.to_field.setPlaceholderText('some_email@example.com')
        self.form_layout.addRow('&To:', self.to_field)

        self.subject_field = QLineEdit(self)
        self.subject_field.setPlaceholderText('Ex: Happy Anniversary!')
        self.form_layout.addRow('&Subject:', self.subject_field)

        self.body_field = QTextEdit(self)
        self.form_layout.addRow(self.body_field)

        self.attachments = FileWindow(parent=self)
        self.form_layout.addRow(self.attachments)

        self.layout.addLayout(self.form_layout)

        self.button_box = QHBoxLayout()

        self.send_button = QPushButton('Send', self)
        self.send_button.clicked.connect(self.send_clicked)

        self.button_box.addStretch(1)
        self.button_box.addWidget(self.send_button)

        self.layout.addLayout(self.button_box)

        self.setLayout(self.layout)

    @Slot()
    def send_clicked(self):
        send_to = self.to_field.text()
        subject = self.subject_field.text()
        text = self.body_field.toPlainText()
        try:
            send_mail(my_email, send_to.split(','), subject, text, self.attachments.get_files())
            QMessageBox.information(self, 'Sending...', 'Your message was sent successfully')
        except smtplib.SMTPException as e:
            QMessageBox.critical(self, 'Sending...', 'SMTPException ({0}): {1}'.format(e.errno, e.strerror))

    def run(self):
        self.show()
        qt_app.exec_()


def decode_content(content):
    result = ''
    for (subj, cs) in decode_header(content or ''):
        if cs:
            result += subj.decode(cs)
        else:
            result += str(subj)
    return result


def mail_header(mail):
    subject = decode_content(mail['subject'])
    return "From: %s\nSubject: %s\n" % (
        email.utils.parseaddr(mail['From'])[1],
        subject
    )


def mail_body(uid, mail):
    text = ''
    attachments = []
    countText = 0
    if mail.is_multipart():
        for payload in mail.get_payload():
            if payload.get_content_type() not in ['text/plain', 'text/html']:
                filename = payload.get_filename()
                filepath = os.path.join(os.path.dirname(__file__), mail_folder, uid.decode('utf-8'), filename)\
                    .replace('/', '\\')
                dir = os.path.dirname(filepath)
                if not os.path.exists(dir):
                    os.makedirs(dir)
                if not os.path.exists(filepath):
                    open(filepath, 'wb').write(payload.get_payload(decode=True))
                attachments.append(filepath)
            else:
                countText += 1
                if countText == 2: text = ''
                text += payload.get_payload(decode=True).decode('utf-8')
    else:
        text = mail.get_payload(decode=True).decode('utf-8')
    return text, attachments


class MailboxWindow(QWidget):
    def __init__(self):
        QWidget.__init__(self)
        self.setMinimumSize(QSize(800, 600))
        self.setWindowTitle('My Mailbox (%s)' % my_email)

        self.layout = QVBoxLayout()

        self.view_box = QHBoxLayout()

        self.mail_list = QListWidget(self)
        self.mail_list.setMaximumWidth(300)
        self.mail_list.itemDoubleClicked.connect(self.mail_list_open)
        self.view_box.addWidget(self.mail_list)

        self.view_mail_box = QVBoxLayout()
        self.mail_view = QWebView(self)
        self.view_mail_box.addWidget(self.mail_view)
        self.attachments = FileWindow(self, files=[])
        self.view_mail_box.addWidget(self.attachments)

        self.view_box.addLayout(self.view_mail_box)

        self.layout.addLayout(self.view_box)

        self.button_box = QHBoxLayout()
        self.refresh_button = QPushButton('&Refresh', self)
        self.refresh_button.clicked.connect(self.refresh_clicked)
        self.send_button = QPushButton('&Send', self)
        self.send_button.clicked.connect(self.send_clicked)

        self.button_box.addStretch(1)
        self.button_box.addWidget(self.refresh_button)
        self.button_box.addWidget(self.send_button)

        self.layout.addLayout(self.button_box)

        self.setLayout(self.layout)

    @Slot(QListWidgetItem)
    def mail_list_open(self, item):
        row = self.mail_list.row(item)
        text, files = mail_body(self.mails[row][0], self.mails[row][1])
        self.mail_view.setHtml(text)
        self.attachments.set_files(files)

    @Slot()
    def refresh_clicked(self):
        self.mails = list(retrieve_mails(datetime.date.today() - datetime.timedelta(1)))
        self.mail_list.clear()
        for (uid, mail) in self.mails:
            self.mail_list.addItem(mail_header(mail))

    @Slot()
    def send_clicked(self):
        self.send_window = SendEmailWindow()
        self.send_window.show()

    def run(self):
        self.show()
        qt_app.exec_()


MailboxWindow().run()

