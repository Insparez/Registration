// Registration app
// Developed by inspare
#pragma once

#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <map>
#include <iterator>
#include <conio.h>
#include "windows.h"
#include <thread>
#include <mutex>
#include <stdlib.h>

using namespace std;
extern map<string, string> accounts; // использование глобального бинарного дерева
void showRules(); // показать правила создания логина и пароля
void inputFields(string&, string&, bool isAcc = false); // поля для ввода данных
void writeToFile(string, string, bool& firstAcc); // запись полей в файл
bool parceFile(map<string, string>& accounts); // парсинг файла в бинарное дерево
bool isLegalName(string);// проверка легитности никнейма
string inputPass();// Пароль со звездочками
bool isLegalPass(string&);// проверка легитности пароля
string generatePass(); // генерирует легитный пароль
string encrypt(string& toEncrypt); // шифровка пароля в файл
string decrypt(string& toDecrypt);// расшифровка пароля из файла
void accMenu(map<string, string>::iterator it);// предоставляет действия в залогиненном аккаунте
void removeAcc(map<string, string>::iterator it); // Удаление аккаунта
void overWritingToFile();// Перезапись аккаунтов с учетом поврежденных данных или при удалении аккаунта
void sleepper(string);//Плавно выводит информацию
void updator();// обновляет строку, а не всю консоль
bool whatToDo();// сздать аккаунт , залогиниться или выйти из приложения
//void changeName(map<string, string>::iterator index); // изменение имени
bool myGetline(string&);// ОГРАНИЧИВАЕТ GETLINE буквы англ алфавита и цифры.
void inputName(string&);// тупо для сокращения кода