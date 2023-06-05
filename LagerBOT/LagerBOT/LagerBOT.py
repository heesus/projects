from asyncio.windows_events import NULL
from email.errors import MessageError
from pickle import TRUE
from unittest import registerResult, removeResult
import pprint
import io
import os
import telebot
from yandex_music.client import Client

pp = pprint.PrettyPrinter(indent=4)
bot = telebot.TeleBot('6280278388:AAFB1JNlpma97j97gO3QVzgqsYrgVpQ8VCQ')
client = Client(token='AQAAAAATN1UfAAG8Xh3J0ecT2EUMsoQpQWTRNCA').init()

@bot.message_handler(commands = ['start'])
def start(message):
    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    massege = "Привет привет, я - бот лагеря. Написан я с божьей помощью. Пока я умею только загружать музыку на дискотеку."
    key_donate = telebot.types.KeyboardButton("/donate")
    key_upload_music = telebot.types.KeyboardButton("/uploadMusic")
    markup.add(key_donate, key_upload_music)
    bot.send_message(message.from_user.id, text=massege, reply_markup=markup)

@bot.message_handler(commands = ['donate'])
def donate(message):
    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_upload_music = telebot.types.KeyboardButton("/uploadMusic")
    markup.add(key_upload_music)
    text = "Спасибо, что захотел меня поддержать\! Вот [ссылка](https://www.tinkoff.ru/cf/7Z2ohnGKe8k) на сбор средств\."
    bot.send_message(message.from_user.id, text, parse_mode='MarkdownV2', reply_markup=markup)

@bot.message_handler(commands = ['uploadMusic'])
def uploadMusic(message):
    text = "Чтобы загрузить треки - напиши их названия и исполнителя. Каждый трек с новой строки."
    bot.send_message(message.from_user.id, text)
    bot.register_next_step_handler(message, search_songs)

def search_songs(message):
    query = message.text.split("\n")
    counter = 0
    text = ""
    flag = True
    print(query)
    for i in query:
        search_result = client.search(i)
        if search_result.best:
            playlist = client.usersPlaylists("1037")
            track = search_result.tracks.results[0]
            if track:
                text = text + str(counter + 1) + ") " + track.artists[0].name + " - " + track.title + "\n"
                counter = counter + 1
                playlist.insertTrack(track.id, track.albums[0].id)

    markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_donate = telebot.types.KeyboardButton("/donate")
    key_uploadMusic = telebot.types.KeyboardButton("/uploadMusic")
    markup.add(key_donate, key_uploadMusic)
    if len(query) > counter:
        bot.send_message(message.from_user.id, "К сожалению, у меня не получилось добавить все треки((((")
    text = "Я добавил " + str(counter) + " трека(-ов):\n" + text
    bot.send_message(message.from_user.id, text)
    text =  "Посмотреть плейлист ты можешь по [ссылке](https://music.yandex.ru/users/odaniilos/playlists/1037)\."
    bot.send_message(message.from_user.id, text, reply_markup=markup, parse_mode='MarkdownV2')
    text = "Что ты хочешь сделать теперь?"
    bot.send_message(message.from_user.id, text, reply_markup=markup)

bot.infinity_polling()