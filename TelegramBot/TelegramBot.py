from google.oauth2 import service_account
from googleapiclient.discovery import build
import pprint
import telebot
import functions.baseUpdater as base
import functions.fileUpdater as f
import emoji
import random
from transliterate import translit

pp = pprint.PrettyPrinter(indent=4)
SCOPES = ['https://www.googleapis.com/auth/drive']
SERVICE_ACCOUNT_FILE = 'client_secret.json'
credentials = service_account.Credentials.from_service_account_file(SERVICE_ACCOUNT_FILE, scopes=SCOPES)
service = build('drive', 'v3', credentials=credentials)
#service.files().delete(fileId='1kB8OE76P7uYWTfVA47NhqCYpe1BBmLJ3').execute()
#pp.pprint(service.files().list(pageSize=100,fields="nextPageToken, files(id, name)").execute())
bot = telebot.TeleBot('')

@bot.message_handler(commands = ['yaAdminPustiBotPj'])
def admin(message):
    bot.send_message(message.from_user.id, "Привет привет, одмен, ты можешь выбрать людей, которых хочешь пнуть - напомнить про доки. Вывожу их имена и количесвто несданных доков.")
    baseFoldersList = base.get_folders_from_base()
    baseFoldersstring = ""
    count = 0
    for i in range(len(baseFoldersList)):
        docsList = list(base.get_doc_from_base_name(baseFoldersList[i][0], baseFoldersList[i][1], baseFoldersList[i][2]).split(" "))
        for j in range(len(docsList)):
            if int(docsList[j]) > 0 and (j!= 16 and j!= 15 and j!= 14):
                count = count + 1
        baseFoldersstring = baseFoldersstring + str(i+1) + ") " + baseFoldersList[i][1] + " " + baseFoldersList[i][0] + " " + baseFoldersList[i][2] + " --- " + str(count) + "\n"
        count = 0
    bot.send_message(message.from_user.id, "Сейчас у меня в базе есть данные о папках этих людей:\n" + baseFoldersstring[:-1])
    bot.send_message(message.from_user.id, "Если я не вывел чью-то папку, то её создавал не я. Напиши Дане - он решит вопросик.")
    bot.send_message(message.from_user.id, "Чтобы пнуть чевовечка напиши ОДНИМ СООБЩЕНИЕМ через пробел их номера в списке(пример сообщения - 1 2 3 5 6 11)\n")
    bot.register_next_step_handler(message, kick)

def kick(message):
    baseFoldersList = base.get_folders_from_base()
    kickList = list(message.text.split(" "))
    for i in kickList:
        id = base.get_id_from_base_name(baseFoldersList[int(i)-1][0], baseFoldersList[int(i)-1][1], baseFoldersList[int(i)-1][2])
        bot.send_message(id, "Привет привет. Мне тут командир нажаловался на тебя. Говорит, что ты не скидываешь доки. Сделай это в ближайшее время.\n")
    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_check = telebot.types.KeyboardButton("/check")
    key_add = telebot.types.KeyboardButton("/add")
    key_missing = telebot.types.KeyboardButton("/missing")
    key_donate = telebot.types.KeyboardButton("/donate")
    key_link = telebot.types.KeyboardButton("/link")
    markup.add(key_check, key_add,key_missing, key_donate, key_link)
    bot.send_message(message.from_user.id, "Я всё отправиль!", reply_markup=markup)


@bot.message_handler(commands = ['start'])
def start(message):
    if base.get_user(str(message.from_user.id)) != []:
        markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
        key_yes = telebot.types.KeyboardButton("Это я")
        markup.add(key_yes)
        question = "О, а я тебя помню, ты же " + base.get_fio(str(message.from_user.id)) + "?"
        bot.send_message(message.from_user.id, question, reply_markup=markup)
        bot.register_next_step_handler(message, folder_finder)
    else:
        markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
        key_yes = telebot.types.KeyboardButton("Да")
        markup.add(key_yes)
        key_no= telebot.types.KeyboardButton("Нет")
        markup.add(key_no)
        question = "Привет, " + str(message.from_user.first_name) + "! Я бот - помошник командира. В будущем ты закинешь сюда свои доки, и я оформлю на тебя кредит)))) Шутка. Ты готов начать?"
        bot.send_message(message.from_user.id, question, reply_markup=markup)
        bot.register_next_step_handler(message, agreement)

@bot.message_handler(commands = ['help'])
def help(message):
    bot.send_message(message.from_user.id, "Ещё не запрогано(((")

@bot.message_handler(commands = ['donate'])
def donate(message):
    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_check = telebot.types.KeyboardButton("/check")
    key_add = telebot.types.KeyboardButton("/add")
    key_missing = telebot.types.KeyboardButton("/missing")
    key_link = telebot.types.KeyboardButton("/link")
    markup.add(key_check, key_add, key_missing, key_link)
    text = "Спасибо, что захотел меня поддержать! Вот [ссылка](https://www.tinkoff.ru/cf/7Z2ohnGKe8k) на сбор средств."
    bot.send_message(message.from_user.id, text, reply_markup=markup, parse_mode="Markdown")

@bot.message_handler(commands = ['link'])
def link(message):
    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_check = telebot.types.KeyboardButton("/check")
    key_add = telebot.types.KeyboardButton("/add")
    key_missing = telebot.types.KeyboardButton("/missing")
    key_donate = telebot.types.KeyboardButton("/donate")
    markup.add(key_check, key_add, key_missing, key_donate)
    text = "Вот ссылка на Твою папку:\n https://drive.google.com/drive/folders/" + base.get_folder_id(message.from_user.id)[0][0]
    bot.send_message(message.from_user.id, text, reply_markup=markup, parse_mode="Markdown")
    
@bot.message_handler(commands = ['check'])
def check(message):
    docs = f.get_files_from_folder(message.from_user.id)
    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_add = telebot.types.KeyboardButton("/add")
    key_missing = telebot.types.KeyboardButton("/missing")
    key_donate = telebot.types.KeyboardButton("/donate")
    key_link = telebot.types.KeyboardButton("/link")
    if len(docs) == 0:
        bot.send_message(message.from_user.id, "Твоя папка пуста.") 
        markup.add(key_add, key_missing, key_donate, key_link)
        text = "Что делаем теперь?"
        bot.send_message(message.from_user.id, text, reply_markup=markup)
    else:
        output = "В твоей папке лежат файлы:\n" + docs
        bot.send_message(message.from_user.id, output)
        markup.add(key_add, key_missing, key_donate, key_link)
        text = "Что делаем теперь?"
        bot.send_message(message.from_user.id, text, reply_markup=markup)
    
@bot.message_handler(commands = ['add'])
def add(message):
    text = """Сейчас надо будет загружать документы. Загрузка происходит по одному документу, не пытайся прикреплять сразу несколько. 
Для этого выбери из списка, что ты хочешь загрузить *(все файлы должны быть в формате pdf, если не указано другое. ВНИМАНИЕ При загрузке какого-либо документа происходит замена старого(если он есть) на новый.)*
/uploadPassport - скан паспорта
/uploadINN - скан инн
/uploadSNILS - скан снилса
/uploadRequisites - реквизиты карты
/uploadCertificate - свидетельство вожатого
/uploadEducation - аттестат \ диплом \ справка из ВУЗа
/uploadEmployment - выписка из трудовой
/uploadCriminal - справка о несудимости
/uploadDrugs - справка о наркотиках
/uploadCovid - ковидный сертик
/uploadMedical - медицинская книжка
/uploadVaccinations - прививочный сертификат
/uploadOPO - результат обследования ОПО
/uploadPOLIS - скан полиса
/uploadFLG - результат флюшки
/uploadCriminalStatement *(док или скрин)* - заявление на справку о несудимости
/uploadDrugsStatement *(док или скрин)* - заявление на справку об отсутствие уголовного преследования за нарко

/show - повторный вызов этого сообщения
Также ты можешь написать /exit, если больше не хочешь загружать доки.
"""
    bot.send_message(message.from_user.id, text, parse_mode="Markdown")
    bot.register_next_step_handler(message, add_file_message)

def add_file_end(message):
    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_check = telebot.types.KeyboardButton("/check")
    key_missing = telebot.types.KeyboardButton("/missing")
    key_donate = telebot.types.KeyboardButton("/donate")
    key_link = telebot.types.KeyboardButton("/link")
    markup.add(key_check, key_missing, key_donate, key_link)
    text = "Что делаем теперь?"
    bot.send_message(message.from_user.id, text, reply_markup=markup)

def add_file_message(message):
    if message.text == "/uploadPassport":
        bot.send_message(message.from_user.id, "Отправь мне скан паспорта")
        bot.register_next_step_handler(message, add_file, 1)
    elif message.text == "/uploadINN":
        bot.send_message(message.from_user.id, "Отправь мне скан ИНН")
        bot.register_next_step_handler(message, add_file, 2)
    elif message.text == "/uploadSNILS":
        bot.send_message(message.from_user.id, "Отправь мне скан снилса")
        bot.register_next_step_handler(message, add_file, 3)
    elif message.text == "/uploadRequisites":
        bot.send_message(message.from_user.id, "Отправь мне реквизиты карты")
        bot.register_next_step_handler(message, add_file, 4)
    elif message.text == "/uploadCertificate":
        bot.send_message(message.from_user.id, "Отправь мне свидетельство вожатого")
        bot.register_next_step_handler(message, add_file, 5)
    elif message.text == "/uploadEducation":
        bot.send_message(message.from_user.id, "Отправь мне аттестат \ диплом \ справку из ВУЗа")
        bot.register_next_step_handler(message, add_file, 6)
    elif message.text == "/uploadEmployment":
        bot.send_message(message.from_user.id, "Отправь мне выписку из трудовой")
        bot.register_next_step_handler(message, add_file, 7)
    elif message.text == "/uploadCriminal":
        bot.send_message(message.from_user.id, "Отправь мне справку о несудимости")
        bot.register_next_step_handler(message, add_file, 8)
    elif message.text == "/uploadDrugs":
        bot.send_message(message.from_user.id, "Отправь мне справку о наркотиках")
        bot.register_next_step_handler(message, add_file, 9)
    elif message.text == "/uploadCovid":
        bot.send_message(message.from_user.id, "Отправь мне ковидный сертификат")
        bot.register_next_step_handler(message, add_file, 10)
    elif message.text == "/uploadMedical":
        bot.send_message(message.from_user.id, "Отправь мне медицинскую книжку")
        bot.register_next_step_handler(message, add_file, 11)
    elif message.text == "/uploadVaccinations":
        bot.send_message(message.from_user.id, "Отправь мне прививочный сертификат")
        bot.register_next_step_handler(message, add_file, 12)
    elif message.text == "/uploadOPO":
        bot.send_message(message.from_user.id, "Отправь мне результат обследования ОПО")
        bot.register_next_step_handler(message, add_file, 13)
    elif message.text == "/uploadPOLIS":
        bot.send_message(message.from_user.id, "Отправь мне скан полиса")
        bot.register_next_step_handler(message, add_file, 14)   
    elif message.text == "/uploadFLG":
        bot.send_message(message.from_user.id, "Отправь мне результат флюшки")
        bot.register_next_step_handler(message, add_file, 15)
    elif message.text == "/uploadCriminalStatement":
        bot.send_message(message.from_user.id, "Отправь мне заявление на справку о несудимости")
        bot.register_next_step_handler(message, add_file, 16)
    elif message.text == "/uploadDrugsStatement":
        bot.send_message(message.from_user.id, "Отправь мне заявление на справку об отсутствие уголовного преследования за нарко")
        bot.register_next_step_handler(message, add_file, 17)
    elif message.text == "/exit":
        add_file_end(message)
    elif message.text == "/show":
        text = """Сейчас надо будет загружать документы. Загрузка происходит по одному документу, не пытайся прикреплять сразу несколько. 
Для этого выбери из списка, что ты хочешь загрузить *(все файлы должны быть в формате pdf, если не указано другое)*
/uploadPassport - скан паспорта
/uploadINN - скан инн
/uploadSNILS - скан снилса
/uploadRequisites - реквизиты карты
/uploadCertificate - свидетельство вожатого
/uploadEducation - аттестат \ диплом \ справка из ВУЗа
/uploadEmployment - выписка из трудовой
/uploadCriminal - справка о несудимости
/uploadDrugs - справка о наркотиках
/uploadCovid - ковидный сертик
/uploadMedical - медицинская книжка
/uploadVaccinations - прививочный сертификат
/uploadOPO - результат обследования ОПО
/uploadPOLIS - скан полиса
/uploadFLG - результат флюшки
/uploadCriminalStatement *(док или скрин)* - заявление на справку о несудимости
/uploadDrugsStatement *(док или скрин)* - заявление на справку об отсутствие уголовного преследования за нарко

/show - повторный вызов этого сообщения
Также ты можешь написать /exit, если больше не хочешь загружать доки.
"""
        bot.send_message(message.from_user.id, text, parse_mode="Markdown")
        bot.register_next_step_handler(message, add_file_message)
    else:
        bot.reply_to(message, "Мне не знакомо это ключевое слово! Попробуй ещё раз.")
        bot.register_next_step_handler(message, add_file_message)


def add_file(message, flag):
    if message.text == "/stop":
        bot.send_message(message.from_user.id, "Я тебя понял. Если ты закончил загружать доки - напиши /exit, чтобы использовать другие функции. Если же ещё не закончил - напиши  /show, чтобы освежить в памяти ключевые слова документов и выбери что-то новое.")
        bot.register_next_step_handler(message, add_file_message)
    else:
        if message.media_group_id: 
            bot.send_message(message.from_user.id, "Пожалуйста, прикрепляй файлы по одному!")
            bot.register_next_step_handler(message, add_file, flag)
        else:
            if flag in [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15] and message.document:
                file_info = bot.get_file(message.document.file_id)
                file = bot.download_file(file_info.file_path)
                bot.reply_to(message, "Пробую загрузить. Это может занять некоторое время.")
                result = f.upload_file(message, service, flag, file_info, file)
            elif message.photo:
                file_info = bot.get_file(message.photo[-1].file_id)
                file = bot.download_file(file_info.file_path)
                bot.reply_to(message, "Пробую загрузить. Это может занять некоторое время.")
                result = f.upload_file(message, service, flag, file_info, file)
            elif message.document:
                file_info = bot.get_file(message.document.file_id)
                file = bot.download_file(file_info.file_path)
                bot.reply_to(message, "Пробую загрузить. Это может занять некоторое время.")
                result = f.upload_file(message, service, flag, file_info, file)
            if 'result' not in dir():
                bot.reply_to(message, "Я не очень понимаю, что ты тут прислал, но мой разум говорит, что я не могу это загрузить на диск. Попробуй снова загрузить нужный документ или напиши /stop, чтобы выбрать другой вид документа.")
                bot.register_next_step_handler(message, add_file, flag)
            elif 'result' in dir():
                if result["exception"] == "notDoc":
                    bot.reply_to(message,  "Я не очень понимаю, что ты тут прислал, но мой разум говорит, что я не могу это загрузить на диск. Попробуй снова загрузить нужный документ или напиши /stop, чтобы выбрать другой вид документа.")
                    bot.register_next_step_handler(message, add_file, flag)
                elif result["exception"] == "notPdfFormat":
                    bot.reply_to(message, "Неверный формат файла! Попробуй загрузить этот документ в формате pdf.")
                    bot.register_next_step_handler(message, add_file, flag)
                elif result["exception"] == "notExceptin" and result["succsess"] == True:
                    base.del_doc_from_base(flag, str(message.from_user.id))
                    bot.send_message(message.from_user.id, "Загрузил! Можешь загрузить другой файл, написав его команду, или закончить, написав /stop.")
                    bot.register_next_step_handler(message, add_file_message)
                elif result["exception"] == "serverBusy":
                    bot.send_message(message.from_user.id, "Сервер сейчас занят. Пришли файл ещё раз или напиши /stop.")
                    bot.register_next_step_handler(message, add_file, flag)
                else:
                    bot.reply_to(message, "Ёбаный прогер! Этот долбаёб не смог нормально всё продумать. Кинь ему в тг(@heesuss) скрин чата с ботом, чтобы он это пофиксил.")
                    bot.register_next_step_handler(message, add_file_message)
            else:
                bot.reply_to(message, "Ёбаный прогер! Этот долбаёб не смог нормально всё продумать. Кинь ему в тг(@heesuss) скрин чата с ботом, чтобы он это пофиксил.")
                bot.register_next_step_handler(message, add_file_message)
        
            

@bot.message_handler(commands = ['missing'])
def missing(message):
    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_check = telebot.types.KeyboardButton("/check")
    key_add = telebot.types.KeyboardButton("/add")
    key_donate = telebot.types.KeyboardButton("/donate")
    key_link = telebot.types.KeyboardButton("/link")
    markup.add(key_check, key_add, key_donate, key_link)
    text = "Не хватает следующих файлов:\n"
    l = list(base.get_doc_from_base(message.from_user.id).split(' '))
    if l[0][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана паспорта\n"
    if l[1][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана ИНН\n"
    if l[2][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана СНИЛСа\n"
    if l[3][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Реквизитов карты\n"
    if l[4][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана свидетельства вожатого\n"
    if l[5][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана документа об образовании\n"
    if l[6][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана выписки из трудовой\n"
    if l[7][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана справки о несудимости\n"
    if l[8][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана справки о  ниркотиках\n"
    if l[9][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Ковидного сертификата\n"
    if l[10][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана медицинской книжки\n"
    if l[11][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана прививочного сертификата\n"
    if l[12][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана результата ОПО\n"
    if l[13][0] != '-':
        text = text + emoji.emojize(":police_car:") + "Скана полиса\n"
    if text == "Не хватает следующих файлов:\n":
        text = "У тебя всё сдано, ты умничка!"
    bot.send_message(message.from_user.id, text, reply_markup=markup)
    if text == "У тебя всё сдано, ты умничка!":
        bot.send_sticker(message.from_user.id, "CAACAgIAAxkBAAEH6p1j-8XHqA8LrXFBHHeuxoJ9SoLuwgACdQEAAj0N6ARJB25KvuGMwi4E")

def agreement(message):
    if message.text == "Нет":
        markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
        key_start = telebot.types.KeyboardButton("/start")
        markup.add(key_start)
        bot.send_message(message.from_user.id, text = "Хорошо, тогда приходи в другой раз.", reply_markup=markup)
    elif message.text == "Да":
        bot.send_message(message.from_user.id, 'Отлично! Тогда давай начинать.\n Напиши свою фамилию.')
        base.add_to_base_id(str(message.from_user.id))
        bot.register_next_step_handler(message, get_surname)
    
def folder_finder(message):
    bot.send_message(message.from_user.id, "Сейчас поищу твою папку на диске. Это займёт какое-то время.")
    id, docs = f.get_name_folder_id(message, service)
    if id == ['1']:
        markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
        key_yes = telebot.types.KeyboardButton("Естесна")
        markup.add(key_yes)
        bot.send_message(message.from_user.id, "Сервер сейчас занят, попробовать снова? (Иллюзия выбора)", reply_markup=markup)
        bot.register_next_step_handler(message, folder_finder)
    elif len(id) == 0:
        bot.send_message(message.from_user.id, "Твоей папки пока нет(\n Сейчас её создам.") 
        f.add_folder(message.from_user.id, service)
        bot.send_message(message.from_user.id, "Я создаль!")
        markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
        key_check = telebot.types.KeyboardButton("/check")
        key_add = telebot.types.KeyboardButton("/add")
        key_missing = telebot.types.KeyboardButton("/missing")
        key_donate = telebot.types.KeyboardButton("/donate")
        key_link = telebot.types.KeyboardButton("/link")
        markup.add(key_check, key_add,key_missing, key_donate, key_link)
        text = """Потрясно, что ты хочешь сделать?
""" + emoji.emojize(":thumbs_up:") + """Нажми /check, если хочешь посмотреть, какие документы уже есть в твоей папке.
""" + emoji.emojize(":thumbs_up:") + """Нажми /add, если хочешь загрузить доки.
""" + emoji.emojize(":thumbs_up:") + """Нажми /missing, есди хочешь посмотреть, каких документов не хватает.
""" + emoji.emojize(":thumbs_up:") + """Нажми /link, если хочешь получить ссылку на твою папку (для проверки отправленных доков).
""" + emoji.emojize(":thumbs_up:") + """Нажми /donate, если хочешь задонатить птрясающему разработчику Даньке Орлову"""
        bot.send_message(message.from_user.id, text, reply_markup=markup)
    else:
        bot.send_message(message.from_user.id, "Я нашёл твою папку!")
        base.update_doc_in_base(docs, message.from_user.id)
        base.add_to_base_folder_id(id[0]['id'], str(message.from_user.id))
        markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
        key_check = telebot.types.KeyboardButton("/check")
        key_add = telebot.types.KeyboardButton("/add")
        key_missing = telebot.types.KeyboardButton("/missing")
        key_donate = telebot.types.KeyboardButton("/donate")
        key_link = telebot.types.KeyboardButton("/link")
        markup.add(key_check, key_add, key_missing, key_donate, key_link)
        text = """Потрясно, что ты хочешь сделать?
""" + emoji.emojize(":thumbs_up:") + """Нажми /check, если хочешь посмотреть, какие документы уже есть в твоей папке.
""" + emoji.emojize(":thumbs_up:") + """Нажми /add, если хочешь загрузить доки.
""" + emoji.emojize(":thumbs_up:") + """Нажми /missing, есди хочешь посмотреть, каких документов не хватает.
""" + emoji.emojize(":thumbs_up:") + """Нажми /link, если хочешь получить ссылку на твою папку (для проверки отправленных доков).
""" + emoji.emojize(":thumbs_up:") + """Нажми /donate, если хочешь задонатить птрясающему разработчику Даньке Орлову"""
        bot.send_message(message.from_user.id, text,reply_markup=markup)
        
def get_surname(message):
    base.add_to_base_surname(message.text, message.from_user.id)
    bot.send_message(message.from_user.id, 'Записал! Теперь напиши имя.')
    bot.register_next_step_handler(message, get_name)

def get_name(message):
    base.add_to_base_name(message.text, message.from_user.id)
    bot.send_message(message.from_user.id, 'Запомнил! Не поверишь) Напиши своё отчество.')
    bot.register_next_step_handler(message, get_patronymic)

def get_patronymic(message):
    base.add_to_base_patronymic(message.text, message.from_user.id)
    bot.send_message(message.chat.id, 'Сохранил!')
    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_yes = telebot.types.KeyboardButton("Всё верно")
    markup.add(key_yes)
    key_no= telebot.types.KeyboardButton("Стой, хочу исправить")
    markup.add(key_no)
    question = "Давай проверим, тебя зовут " + base.get_fio(message.from_user.id) + "?"
    bot.send_message(message.from_user.id, text=question, reply_markup=markup)
    bot.register_next_step_handler(message, check_full_name)

def check_full_name(message):
    if message.text == "Всё верно":
        bot.send_message(message.chat.id, 'Кайфули, сейчас проверю, есть ли твоя папка с документами. Это займёт немного времени.')
        folder_finder(message)
    elif message.text == "Стой, хочу исправить":
        bot.send_message(message.chat.id, 'Хорошо, давай ещё раз. \n Напиши свою фамилию.')
        bot.register_next_step_handler(message, get_surname)


#@bot.message_handler(content_types = ['text'])
#def start_handler(message):
#    bot.reply_to(message, "Я не понимаю, что ты пишешь. Обратись в окошко /start или /help, там тебе помогут.")
#@bot.message_handler(content_types = ['text'])
#def start_handler(message):
#    if base.get_user(str(message.from_user.id)) == []:
#        bot.send_message(message.from_user.id, "О, привет, ты у меня впервые? Напиши /start, чтобы познакомиться со мной.")
#    bot.register_next_step_handler(message, start)

bot.enable_save_next_step_handlers(delay=2)
bot.load_next_step_handlers()

bot.infinity_polling()