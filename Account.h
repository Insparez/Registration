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
extern map<string, string> accounts; // ������������� ����������� ��������� ������
void showRules(); // �������� ������� �������� ������ � ������
void inputFields(string&, string&, bool isAcc = false); // ���� ��� ����� ������
void writeToFile(string, string); // ������ ����� � ����
bool parceFile(map<string, string>& accounts); // ������� ����� � �������� ������
bool isLegalName(string);// �������� ���������� ��������
string inputPass();// ������ �� �����������
bool isLegalPass(string&);// �������� ���������� ������
string generatePass(); // ���������� �������� ������
string encrypt(string& toEncrypt); // �������� ������ � ����
string decrypt(string& toDecrypt);// ����������� ������ �� �����
void accMenu(map<string, string>::iterator it);// ������������� �������� � ������������ ��������
void removeAcc(map<string, string>::iterator it); // �������� ��������
void overWritingToFile();// ���������� ��������� � ������ ������������ ������ ��� ��� �������� ��������
void sleepper(string);//������ ������� ����������
void updator();// ��������� ������, � �� ��� �������
bool whatToDo();// ������ ������� , ������������ ��� ����� �� ����������
void changeName(map<string, string>::iterator index); // ��������� �����
void changePass(map<string, string>::iterator index); // ��������� �����
bool myGetline(string&);// ������������ GETLINE ����� ���� �������� � �����.
void inputName(string&);// ���� ��� ���������� ����