from aiogram import Bot, Dispatcher, executor, types
import time
from yandex_music.client import Client
import aiogram
from aiogram.utils.helper import Helper, HelperMode, ListItem
from aiogram.contrib.fsm_storage.memory import MemoryStorage
from aiogram.types import ParseMode, InputMediaPhoto, InputMediaVideo, ChatActions
from aiogram.utils.markdown import text, bold, italic, code, pre

class States(Helper):
    mode = HelperMode.snake_case
    STATE_0 = ListItem()
    STATE_1 = ListItem()

# Токен, выданный BotFather в телеграмме
API_TOKEN = '6280278388:AAFB1JNlpma97j97gO3QVzgqsYrgVpQ8VCQ'

bot = Bot(token=API_TOKEN)
dp = Dispatcher(bot, storage=MemoryStorage())
client = Client(token='AQAAAAATN1UfAAG8Xh3J0ecT2EUMsoQpQWTRNCA').init()

@dp.message_handler(commands = ['start'])
async def start(message: types.Message):
    markup = aiogram.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    massege = "Привет привет, я - бот лагеря. Написан я с божьей помощью. Пока я умею только загружать музыку на дискотеку."
    key_donate = aiogram.types.KeyboardButton("/donate")
    key_upload_music = aiogram.types.KeyboardButton("/uploadMusic")
    markup.add(key_donate, key_upload_music)
    state = dp.current_state(user=message.from_user.id)
    await state.set_state(States.all()[0])
    await bot.send_message(message.from_user.id, text=massege, reply_markup=markup)

@dp.message_handler(commands = ['donate'], state = States.STATE_0)
async def donate(message: types.Message):
    markup = aiogram.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_upload_music = aiogram.types.KeyboardButton("/uploadMusic")
    markup.add(key_upload_music)
    text = "Спасибо, что захотел меня поддержать\! Вот [ссылка](https://www.tinkoff.ru/cf/7Z2ohnGKe8k) на сбор средств\."
    await bot.send_message(message.from_user.id, text, parse_mode='MarkdownV2', reply_markup=markup)

@dp.message_handler(commands = ['uploadMusic'], state = States.STATE_0)
async def uploadMusic(message: types.Message):
    text = "Чтобы загрузить треки - напиши их названия и исполнителя. Каждый трек с новой строки."
    state = dp.current_state(user=message.from_user.id)
    print(state)
    await state.set_state(States.all()[1])
    await bot.send_message(message.from_user.id, text)

@dp.message_handler(state=States.STATE_1)
async def search_songs(message: types.Message):
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

    markup = aiogram.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
    key_donate = aiogram.types.KeyboardButton("/donate")
    key_uploadMusic = aiogram.types.KeyboardButton("/uploadMusic")
    markup.add(key_donate, key_uploadMusic)
    if len(query) > counter:
        bot.send_message(message.from_user.id, "К сожалению, у меня не получилось добавить все треки((((")
    text = "Я добавил " + str(counter) + " трека(-ов):\n" + text + "\n"
    text = text + "Посмотреть плейлист ты можешь по [ссылке](https://music.yandex.ru/users/odaniilos/playlists/1037).\n"
    text = text + bold("Что ты хочешь сделать теперь?")
    state = dp.current_state(user=message.from_user.id)
    await state.set_state(States.all()[0])
    await bot.send_message(message.from_user.id, text, reply_markup=markup, parse_mode=ParseMode.MARKDOWN)


async def shutdown(dispatcher: Dispatcher):
    await dispatcher.storage.close()
    await dispatcher.storage.wait_closed()

if __name__ == '__main__':
    executor.start_polling(dp, on_shutdown=shutdown)