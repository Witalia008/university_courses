import smtplib
from os.path import basename
from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.utils import COMMASPACE, formatdate
import imaplib
import email
import datetime
import sys

my_email = 'username@ukr.net'
my_password = 'password'
smtp_server = 'smtp.ukr.net'
smtp_port = 465
imap_server = 'imap.ukr.net'
imap_port = 993


def send_mail(send_from, send_to, subject, text, files=None):
    assert isinstance(send_to, list)

    msg = MIMEMultipart(
        From=send_from,
        To=COMMASPACE.join(send_to),
        Date=formatdate(localtime=True),
        Subject=subject
    )
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
        yield email.message_from_bytes(raw_email)

    imap.close()
    imap.logout()


# send_mail(my_email, [my_email], 'Test mail', 'Hello, World!', ['main.py'])
# inbox = list(retrieve_mails(datetime.date.today() - datetime.timedelta(3)))


from PySide.QtCore import *
from PySide.QtGui import *

qt_app = QApplication(sys.argv)


class FileWindow(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)

        self.layout = QVBoxLayout()
        self.setWindowTitle('hehe')
        self.setMinimumWidth(800)

        self.layout.addWidget(QLabel('Attachments list:', self))

        self.files_list = QListWidget(self)
        self.layout.addWidget(self.files_list)

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

        self.attachments = FileWindow(self)
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
            QMessageBox.information(self, 'Sending...', 'Your message was sent')
        except smtplib.SMTPException as e:
            QMessageBox.critical(self, 'Sending...', 'SMTPException ({0}): {1}'.format(e.errno, e.strerror))

    def run(self):
        self.show()
        qt_app.exec_()


# FileWindow().run()
SendEmailWindow().run()

