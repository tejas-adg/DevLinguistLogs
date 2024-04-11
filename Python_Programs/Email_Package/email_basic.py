import smtplib, os, re, sys, ssl
from getpass import getpass

sender_email = "shankyhunter1@gmail.com"
receiver_email = "tejasam37@gmail.com"
msg = '''\
Subject: Hi There!

This is a plain-text email sent from a python script'''

ssl_port = 465
password = input("Enter password :- ")

default_context = ssl.create_default_context()

with smtplib.SMTP_SSL("smtp.gmail.com", ssl_port, context = default_context) as server:
    server.login(sender_email, password)

    server.sendmail(sender_email, receiver_email, msg)
