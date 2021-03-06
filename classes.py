# -*- coding: utf-8 -*-

import config
import telebot
import sqlite3
from telebot import types
import time
import datetime
import sys

from keyboard import *
from config import *
from bot import *

class User:
    chat_id = 0
    user_id = 0
    firs_name = "(Не установлено)"
    last_name = "(Не установлено)"
    username = "(Не установлено)"
    group = "(Не установлено)"
    stream = 0
    status = 0
    sign_pic = ""
    sign_width = 0
    sign_height = 0
    def __init__(self, user_info, chat_id):
        con = sqlite3.connect('db/database.sql')
        cur = con.cursor()
        self.chat_id = chat_id
        self.user_id = user_info.id
        cur.execute('SELECT name, surname, username, "group", first_name, last_name, status, sign_pic, sign_width, sign_height FROM users WHERE chat_id = {}'.format(self.chat_id))
        user = cur.fetchone()
        con.close()
        if user[0] != None and user[0] != "None":
            self.first_name = user[0]
        elif user[4] != None and user[4] != "None":
            self.first_name = user[4]
        else:
            self.first_name = "(Не установлено)"
        if user[1] != None and user[1] != "None":
            self.last_name = user[1]
        elif user[5] != None and user[5] != "None":
            self.last_name = user[5]
        else:
            self.last_name = "(Не установлено)"
        if user[2] != None and user[2] != "None":
            self.username = user[2]
        else:
            self.username = "(Не установлено)"
        if user[3] != None and user[3] != "None":
            self.group = user[3]
        else:
            self.group = "(Не установлено)"
        if user[7] != None and user[7] != "None":
            self.sign_pic = user[7]
        else:
            self.sign_pic = ""
        self.stream = stream(self.group)
        self.sign_width = user[8]
        self.sign_height = user[9]
        try:
            self.status = user[6]
        except:
            self.status = 0