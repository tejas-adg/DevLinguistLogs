import os, re, sys
from urllib.parse import quote_plus


def bold(text):
    return '<b>' + text + '</b>'

def italic(text):
    return '<i>' + text + '</i>'

def underline(text):
    return '<u>' + text + '</u>'

def newLine():
    return '<br>'

def link(text = None, url = None):
    if ((text is None) and (url is None)):
        return None
    elif ((text is None) and (url is not None)):
        text = ""
    elif ((text is not None) and (url is None)):
        url = 'https://www.google.com/search?q=' + quote_plus(text.strip())

    return "<a href=\"" + url + "\">" + text + "</a>"

def a_tag(attrs):
    return "<a " + " ".join([key + "=" + "\"" + attrs[key] + "\"" for key in attrs if not "text" in key]) + ">" + attrs["text"] + "</a>"

def img_tag(attrs):
    return "<a " + " ".join([key + "=" + "\"" + attrs[key] + "\"" for key in attrs]) + ">"

def p_tag(attrs):
    return "<p " + " ".join([key + "=" + "\"" + attrs[key] + "\"" for key in attrs if not "text" in key]) + ">" + attrs["text"] + "</p>"

def html_tag(text):
    return "<html>" + text + "</html>"

def body_tag(text):
    return "<body>" + text + "</body"
