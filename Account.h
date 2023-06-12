#pragma once
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

using namespace std;

extern map<string, string> accounts; // ������������� ����������� ��������� ������
bool startMenu(); // ������� ������� ��� ������������
void inputFields(string&, string&, bool isAcc = false); // ���� ��� ����� ������
void writeToFile(string, string, bool firstAcc = true); // ������ ����� � ����
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
