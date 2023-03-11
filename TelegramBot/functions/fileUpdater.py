from . import baseUpdater as base
from googleapiclient.http import MediaFileUpload
import os

def del_match(name, service):
    while True:
        try:
            results = service.files().list(pageSize=100, fields="files(id)", q="name contains '" + name + "'").execute()
        except:
            pass
        else:
            break
    if results['files']:
        for i in results['files']:
            while True:
                try:
                    service.files().delete(fileId=i['id']).execute()
                except:
                    pass
                else:
                    break


def create_media_file(message, flag, file_info):
    fio = base.get_shortcut_fio(message.from_user.id)
    if flag == 1:
        name = "1_" + fio + "_паспорт.pdf"
    elif flag == 2:
        name = "2_" + fio + "_ИНН.pdf"
    elif flag == 3:
        name = "3_" + fio + "_СНИЛС.pdf"
    elif flag == 4:
        name = "4_" + fio + "_МИР.pdf"
    elif flag == 5:
        name = "5_" + fio + "_СвидВож.pdf"
    elif flag == 6:
        name = "6_" + fio + "_ДокОбр.pdf"
    elif flag == 7:
        name = "7_" + fio + "_СЗВ.pdf"
    elif flag == 8:
        name = "8_" + fio + "_суд.pdf"
    elif flag == 9:
        name = "9_" + fio + "_нарк.pdf"
    elif flag == 10:
        name = "10_" + fio + "_QR.pdf"
    elif flag == 11:
        name = "11_" + fio + "_МедКниж.pdf"
    elif flag == 12:
        name = "12_" + fio + "_прививки.pdf"
    elif flag == 13:
        name = "13_" + fio + "_ОПО.pdf"
    elif flag == 14:
        name = "14_" + fio + "_полис.pdf"   
    elif flag == 15:
        name = fio + "_ФЛГ"
        path =  file_info.file_path
        for i in range(len(path)):
            if path[i] == ".":
                name = name + path[i:]
    elif flag == 16:
        name = fio + "_ЗаявлСуд"
        if message.photo:
            path =  file_info.file_path
            for i in range(len(path)):
                if path[i] == ".":
                    name = name + path[i:]
        if message.document:
            path =  file_info.file_path
            for i in range(len(path)):
                if path[i] == ".":
                    name = name + path[i:]
    elif flag == 17:
        name = fio + "_ЗаявлНарк"
        if message.photo:
            path =  file_info.file_path
            for i in range(len(path)):
                if path[i] == ".":
                    name = name + path[i:]
        if message.document:
            path =  file_info.file_path
            for i in range(len(path)):
                if path[i] == ".":
                    name = name + path[i]
    file_metadata = {
                'name': name,
                'parents': [base.get_folder_id(message.from_user.id)[0][0]]
            }
    return file_metadata



def add_folder(id, service):
    folder_id = "1ghfJjrvFjBE7TEqLn_rPWSgGGYGS_KMW"
    name = base.get_fio(id)
    file_metadata = {
        'name': name,
        'mimeType': 'application/vnd.google-apps.folder',
         'parents': [folder_id]
    }
    file_permission = {"role": "reader", "type": "anyone"}
    while True:
        try:
            r = service.files().create(body=file_metadata,fields='id').execute()
            service.permissions().create(body=file_permission, fileId=r.get("id")).execute()
        except:
            pass
        else:
            break
    base.add_to_base_folder_id(r['id'], str(id))
        


def get_name_folder_id(message, service):
    if base.get_someone_busy() == []:
        base.add_busy(str(message.from_user.id))
        while True:
            try:
                results = service.files().list(pageSize=100, fields="files(id)", q="name contains '" + str(base.get_user(message.from_user.id)[0][1] + " " + base.get_user(message.from_user.id)[0][0] + " " + base.get_user(message.from_user.id)[0][2]) + "'").execute()
            except:
                pass
            else:
                break
        if len(results['files']) == 0:
            docs = {'files': []}
        else:
            while True:
                try:
                    docs = service.files().list(pageSize=100, fields="files(name)", q="'" + results['files'][0]['id'] + "' in parents").execute()
                except:
                    pass
                else:
                    break
        base.del_busy(str(message.from_user.id))
        return results['files'], docs['files']
    else:
        return ['1'], []

def get_files_from_folder(id):
    docsString = base.get_doc_from_base(id)
    docsList = list(docsString.split(" "))
    availableDocs = ""
    for i in range(len(docsList)):
        if int(docsList[i]) < 0:
            availableDocs = availableDocs + get_doc_name_from_flag(id,i+1) + "\n"
    return availableDocs

def get_doc_name_from_flag(id,flag):
    shortcutFio = base.get_shortcut_fio(id)
    if flag == 1:
        name = "1_" + shortcutFio + "_паспорт.pdf"
    elif flag == 2:
        name = "2_" + shortcutFio + "_ИНН.pdf"
    elif flag == 3:
        name = "3_" + shortcutFio + "_СНИЛС.pdf"
    elif flag == 4:
        name = "4_" + shortcutFio + "_МИР.pdf"
    elif flag == 5:
        name = "5_" + shortcutFio + "_СвидВож.pdf"
    elif flag == 6:
        name = "6_" + shortcutFio + "_ДокОбр.pdf"
    elif flag == 7:
        name = "7_" + shortcutFio + "_СЗВ.pdf"
    elif flag == 8:
        name = "8_" + shortcutFio + "_суд.pdf"
    elif flag == 9:
        name = "9_" + shortcutFio + "_нарк.pdf"
    elif flag == 10:
        name = "10_" + shortcutFio + "_QR.pdf"
    elif flag == 11:
        name = "11_" + shortcutFio + "_МедКниж.pdf"
    elif flag == 12:
        name = "12_" + shortcutFio + "_прививки.pdf"
    elif flag == 13:
        name = "13_" + shortcutFio + "_ОПО.pdf"
    elif flag == 14:
        name = "14_" + shortcutFio + "_полис.pdf"   
    elif flag == 15:
        name = shortcutFio + "_ФЛГ"
    elif flag == 16:
        name = shortcutFio + "_ЗаявлСуд"
    elif flag == 17:
        name = shortcutFio + "_ЗаявлНарк"
    return name

def upload_file(message, service, flag, file_info, file):
    result = {"exception": "notExceptin", "succsess": True}
    if base.get_someone_busy() == []:
        base.add_busy(str(message.from_user.id))
        if flag in [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]:
            if message.document == None:
                result["succsess"] = False
                result["exception"] = "notDoc"
            elif (file_info.file_path)[-3:] != "pdf":
                result["exception"] = "notPdfFormat"
                result["succsess"] = False
            else:
                if flag == 8:
                    del_match(base.get_shortcut_fio(message.from_user.id) + "_ЗаявлСуд", service)
                if flag == 9:
                    del_match(base.get_shortcut_fio(message.from_user.id) + "_ЗаявлНарк", service)
                file_metadata = create_media_file(message, flag, file_info)
                del_match(file_metadata['name'], service)
                with open("cash/" + message.document.file_name, 'wb') as new_file:
                    new_file.write(file)
                while True:
                    try:
                        service.files().create(body=file_metadata, media_body=MediaFileUpload("cash/" + message.document.file_name, resumable=True), fields='id').execute()
                    except:
                        pass
                    else:
                        break
                os.remove("cash/" + message.document.file_name)
        else:
            if message.photo:
                file_metadata = create_media_file(message, flag, file_info)
                del_match(file_metadata['name'], service)
                with open("cash/" + "file.jpg", 'wb') as new_file:
                    new_file.write(file)
                while True:
                    try:
                        service.files().create(body=file_metadata, media_body=MediaFileUpload("cash/" + "file.jpg", resumable=True), fields='id').execute()
                    except:
                        pass
                    else:
                        break
                os.remove("cash/" + "file.jpg")
            elif message.document:
                if file_info.file_path[-3:] != "pdf":
                    file_metadata = create_media_file(message, flag, file_info)
                    del_match(file_metadata['name'], service)
                    with open("cash/" + message.document.file_name, 'wb') as new_file:
                        new_file.write(file)
                    while True:
                        try:
                            service.files().create(body=file_metadata, media_body=MediaFileUpload("cash/" + message.document.file_name, resumable=True), fields='id').execute()
                        except:
                            pass
                        else:
                            break
                    os.remove("cash/" + message.document.file_name)
                else:
                    result["exception"] = "notPdfFormat"
                    result["succsess"] = False
            else:
                result["exception"] = "notPdfFormat"
                result["succsess"] = False
        base.del_busy(str(message.from_user.id))
        return result
    else:
        result["exception"] = "serverBusy"
        result["succsess"] = False
        return result