import sqlite3

def get_files_str(result):
    output = ""
    result = sorted(result, key = my_key)
    for i in range(len(result)):
        output = output + str(result[i].get('name')) + "\n"
    return output

def my_key(a):
    a = a['name']
    try:
        int(a[:2])
    except:
        return int(a[0])
    else:
        return int(a[:2])

def get_user(id):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("SELECT name, surname, patronymic FROM Users_id WHERE id = ?", (id,))
    result = cursor.fetchall()
    conn.close()
    return result

def get_someone_busy():
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("SELECT id FROM Users_id WHERE busy = ?", ('1',))
    result = cursor.fetchall()
    conn.close()
    return result

def add_busy(id):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("UPDATE Users_id SET busy = ? WHERE id = ?" , ('1', id,))
    conn.commit()
    conn.close()

def del_busy(id):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("UPDATE Users_id SET busy = ? WHERE id = ?" , (0, id,))
    conn.commit()
    conn.close()

def add_to_base_id(id):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("insert into Users_id values (?, Null, Null, Null, Null, '1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17', 0)" , (id,))
    conn.commit()
    conn.close()

def add_to_base_folder_id(folder_id, id):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("UPDATE Users_id SET folder_id = ? WHERE id = ?" , (folder_id,id,))
    conn.commit()
    conn.close()

def get_folder_id(id):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("SELECT folder_id FROM Users_id WHERE id = ?", (id,))
    result = cursor.fetchall()
    conn.close()
    return result

def add_to_base_name(name, id):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("UPDATE Users_id SET name = ? WHERE id = ?" , (name,id,))
    conn.commit()
    conn.close()

def add_to_base_patronymic(patronymic, id):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("UPDATE Users_id SET patronymic = ? WHERE id = ?" , (patronymic,id,))
    conn.commit()
    conn.close()

def add_to_base_surname(surname, id):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("UPDATE Users_id SET surname = ? WHERE id = ?" , (surname,id,))
    conn.commit()
    conn.close()

def get_doc_from_base(id):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("SELECT missing FROM Users_id WHERE id = ?", (id,))
    result = cursor.fetchall()
    conn.close()
    return result[0][0]

def get_doc_from_base_name(name, surname, patronymic):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("SELECT missing FROM Users_id WHERE name  = ? AND surname  = ? AND patronymic = ?", (name, surname, patronymic, ))
    result = cursor.fetchall()
    conn.close()
    return result[0][0]

def get_id_from_base_name(name, surname, patronymic):
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("SELECT id FROM Users_id WHERE name  = ? AND surname  = ? AND patronymic = ?", (name, surname, patronymic, ))
    result = cursor.fetchall()
    conn.close()
    return result[0][0]

def del_doc_from_base(flag, id):
    missing = list(get_doc_from_base(id).split(" "))
    missing[flag-1] = '-' + str(flag)
    newMissing = ""
    for i in range(len(missing)):
        newMissing = newMissing + missing[i] + " "
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("UPDATE Users_id SET missing = ? WHERE id = ?" , (newMissing[:-1],id,))
    conn.commit()
    conn.close()

def get_folders_from_base():
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("SELECT name, surname, patronymic FROM Users_id")
    result = cursor.fetchall()
    conn.close()
    return result

def update_doc_in_base(docs,id):
    missing = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17']
    newMissing = ""
    for i in docs:
        if i['name'][:2] == "1_":
            missing[0] = "-1"
        if i['name'][:2] == "2_":
            missing[1] = "-2"
        if i['name'][:2] == "3_":
            missing[2] = '-3'
        if i['name'][:2] == "4_":
            missing[3] = '-4'
        if i['name'][:2] == "5_":
            missing[4] = '-5'
        if i['name'][:2] == "6_":
            missing[5] = '-6'
        if i['name'][:2] == "7_":
            missing[6] = '-7'
        if i['name'][:2] == "8_":
            missing[7] = '-8'
        if i['name'][:2] == "9_":
            missing[8] = '-9'
        if i['name'][:2] == "10":
            missing[9] = '-10'
        if i['name'][:2] == "11":
            missing[10] = '-11'
        if i['name'][:2] == "12":
            missing[11] = '-12'
        if i['name'][:2] == "13":
            missing[12] = '-13'
        if i['name'][:2] == "14":
            missing[13] = '-14'
        if i['name'].find("ФЛГ") != -1:
            missing[14] = '-15'
        if i['name'].find("ЗаявлСуд") != -1:
            missing[15] = '-16'
        if i['name'].find("ЗаявлНарк") != -1:
            missing[16] = '-17'
    for i in range(len(missing)):
        newMissing = newMissing + missing[i] + " "
    conn = sqlite3.connect('users_id.db', timeout=10.0)
    cursor = conn.cursor()
    cursor.execute("UPDATE Users_id SET missing = ? WHERE id = ?" , (newMissing[:-1],id,))
    conn.commit()
    conn.close()


def get_fio(id):
    return str(get_user(id)[0][1]) + " " + str(get_user(id)[0][0]) + " " + str(get_user(id)[0][2])

def get_shortcut_fio(id):
    return str(get_user(id)[0][1]) + "_" + str(get_user(id)[0][0][0]) + str(get_user(id)[0][2][0])