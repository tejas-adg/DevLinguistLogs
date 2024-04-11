import smtplib, ssl, os, re, sys
from email import encoders
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

class Email_Sender:
    def __init__(self, _sender = None, _receiver = None, _subject = None, _message = None, _mime = None):
        self.sender_email = _sender
        self.receiver_email = _receiver
        self.subject = _subject
        self.message = _message
        self.mime_type = _mime
        self.cc_emails = None
        self.bcc_emails = None
        self.html_message = None
        self.password = None
        self.smtp_server = None
        self.smtp_port = None
        self.mime_obj = None

    def set_password(self, text):
        self.password = text

    def set_smtp(self, server, port):
        self.smtp_server = server
        self.smtp_port = port

    def set_sender_email(self, email_id):
        self.sender_email = email_id

    def set_receiver_email(self, email_id):
        self.receiver_email = email_id

    def set_subject(self, text):
        self.subject = text

    def set_message(self, text):
        self.message = text

    def set_cc_emails(self, email_lis):
        self.cc_emails = ', '.join(email_lis)

    def set_bcc_emails(self, email_lis):
        self.bcc_emails = ', '.join(email_lis)

    def set_mime_type(self, type_str):
        self.mime_type = type_str

    def add_html_message(self, html_text):
        self.html_message = html_text

    def add_attachment(self, paths):
        if self.mime_obj is None:
            self.create_mime()
        for path in paths:
            if not os.path.isfile(path):
                print(f"[email_class] ERROR: Please pass a file to attach\nDoes not exist :-  {path}")
                continue
            part = None
            with open(path, 'rb') as attachment:
                part = MIMEBase("application", "octet-stream")
                part.set_payload(attachment.read())
            encoders.encode_base64(part)
            part.add_header("Content-Disposition", "attachment", filename = os.path.basename(path))
            self.mime_obj.attach(part)


    def create_mime(self, ops = None, ret = False):
        if self.mime_obj is not None:
            return None

        if ((ops is None) and (self.mime_type is None)):
            self.mime_obj = MIMEMultipart()
        elif ops is not None:
            self.mime_obj = MIMEMultipart(ops)
        else:
            self.mime_obj = MIMEMultipart(self.mime_type)
        self.mime_obj["To"] = self.receiver_email
        self.mime_obj["From"] = self.sender_email
        self.mime_obj["Subject"] =  self.subject
        if self.cc_emails is not None:
            self.mime_obj["Cc"] = self.cc_emails
        if self.bcc_emails is not None:
            self.mime_obj["Bcc"] = self.bcc_emails
        if self.message is not None:
            self.mime_obj.attach(MIMEText(self.message, "plain"))
        if self.html_message is not None:
            self.mime_obj.attach(MIMEText(self.html_message, "html"))
        if ret:
            return self.mime_obj

    def mime_as_string(self):
        return self.mime_obj.as_string()

    def send_email(self):
        self.create_mime()
        with smtplib.SMTP_SSL(self.smtp_server, self.smtp_port, context = ssl.create_default_context()) as server:
            if ((self.password is None) or (self.password == "")):
                from getpass import getpass
                self.password = getpass(prompt = f"Password for {self.sender_email}")
            server.login(self.sender_email, self.password)
            server.sendmail(self.sender_email, self.receiver_email, self.mime_obj.as_string())
