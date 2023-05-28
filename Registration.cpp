// Registration app
// Developed by inspare

#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

bool startMenu(); // создать аккаунт или залогиниться
void inputFields(string&, string&, bool isAcc = false); // поля для ввода данных
void writeToFile(string, string, bool firstAcc = true); // запись полей в файл
bool parceFile(map<string, string>& accounts); // парсинг файла в контейнер
bool isLegalName(string);// проверка легитности никнейма
bool isLegalPass(string);// проверка легитности пароля
string generatePass(); // генерирует легитный пароль
string encrypt(string& toEncrypt); // шифровка пароля в файл
string decrypt(string& toDecrypt);// расшифровка пароля из файла

int main()
{
	srand(time(0));
	bool isAcc = startMenu();
	bool isWrong = true; // продолжать запрашивать поля воода пока не будет введено верное
	string nickName{ "FIR" };
	string passWord;
	map<string, string> accounts;
	ofstream fout;
	fout.open("Accounts.txt", ofstream::app);
	fout.close();
	if (isAcc)
	{
		if (parceFile(accounts))
		{
			cerr << "No accounts!." << endl;
			exit(0);
		}

		while (isWrong)
		{
			inputFields(nickName, passWord, true);
			auto it = accounts.find(nickName);
			if (it != accounts.end() && passWord == decrypt(it->second))
			{
				cout << "Succsesfully!";
				isWrong = false;
			}
			else {
				cout << "Wrong name or password!" << endl;
			}
		}
	}
	else {
		inputFields(nickName, passWord);
		bool firstAcc = parceFile(accounts);
		while (accounts.count(nickName))
		{
			cout << "Sorry name is occupied." << endl;
			inputFields(nickName, passWord);
		}
		writeToFile(nickName, encrypt(passWord), firstAcc);
	}
	system("pause");
}

bool startMenu() {
	cout << "Welcome to the start page." << "\nDo you have an account? y/n: ";
	char yn;
	while (cin >> yn)
	{
		yn = tolower(yn);
		if (yn == 'y')
		{
			return true;
		}
		else if (yn == 'n') {

			return false;
		}
		else {
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Try only y(yes) or n(no): ";
		}
	}
}
void inputFields(string& nick, string& pass, bool isAcc) {
	if (!isAcc) // Если нет аккаунта то вводим легальные значения
	{
	cout << "Enter your nickname: ";
	getline(cin >> ws, nick);
		while (!isLegalName(nick)) {
			cout << "Enter your nickname: ";
			getline(cin >> ws, nick);// ws нужен для того чтобы избавиться от пробелных символов после cin в startmenu()
		}
		cout << "Enter your password: ";
		getline(cin >> ws, pass);
		while (!isLegalPass(pass))
		{
			cout << "Enter your password: ";
			getline(cin >> ws, pass);
		}
	}
	else { // если аккаунт есть то без разницы что вводить т.к проверятется только наличие имени
		cout << "Enter your nickname: ";
		getline(cin >> ws, nick);
	cout << "Enter your password: ";
	getline(cin >> ws, pass);
	}

}
void writeToFile(string nickName, string passWord, bool firstAcc) {
	ofstream fout;
	fout.open("Accounts.txt", ofstream::app);
	if (fout.is_open())
	{
		if (firstAcc) {
			fout << "-----------------------------" << "\n" << nickName << "\n" << passWord << "\n" << "-----------------------------" << endl;
		}
		else {
			fout << nickName << "\n" << passWord << "\n" << "-----------------------------" << endl;
		}
		cout << "Account succsesfully created!" << endl;
	}
	else {
		cerr << "Somtheing went wrong.";
	}
	fout.close();
}
bool parceFile(map<string, string>& accounts) {
	ifstream fin;
	fin.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		fin.open("Accounts.txt");
	}
	catch (const std::exception& ex)
	{
		cerr << "Error of openning the file, " << ex.what();
		exit(0);
	}
	string input = "";
	vector<string> acc;
	while (fin.good())
	{
		    input = "";
			try
			{
			getline(fin, input);
			}
			catch (const std::exception&)
			{
				break;
			}
			if (fin.eof())
			{
				break;
			}
			acc.push_back(input);
	}
	acc.push_back(input);
	for (auto i = acc.begin(), j= acc.begin(); i < acc.end(); i++)
	{
		if (distance(i, acc.end()) >= 4 && *i == "-----------------------------" && !(i + 1)->empty() && *(i + 1) != "-----------------------------" && !(i + 2)->empty() && *(i + 2) != "-----------------------------" && *(i + 3) == "-----------------------------")
		{
			j = i+2;
			accounts.insert(make_pair(*(i+1), *(j)));
			i += 2;
		}else{
			continue;
		}
	}
	fin.close();
	if (!accounts.size())
	{
		return true;
	}
	else {
		return false;
	}
}
bool isLegalName(string nickName) {
	if (nickName.size() < 4 || nickName.size() > 15)
	{
		cerr << "Nickname have to contain from 4 to 15 symbols!" << endl;
		return false;
	}
	bool onetimes = true;
	try
	{
		if (isdigit(nickName[0])) {
			cerr << "Name cant start with digit" << endl;
			return false;
		}
		else {
			long long a = stoll(nickName);
			cout << "Nick doesnt contain only digits." << endl;
			return false;
		}
	}
	catch (const std::exception&)
	{
		for (int i = 0; i < nickName.size(); i++)
		{
			if (!isalnum(nickName[i]))
			{
				if (nickName[i] == '_' && i != 0 && i != nickName.size() - 1 && onetimes)//Проверка наличия единсвтенного _ в нике и в серединке
				{
					onetimes = false;
					continue;
				}
				cerr << "Nickname can contains only a-z, A-Z, 0-9 and _ in the middle" << endl;
				return false;
			}

		}
		return true;
	}
}
bool isLegalPass(string pass) {
	bool lower = false;
	bool upper = false;
	bool digit = false;
	bool punct = false;
	if (pass.size() < 8 || pass.size() > 20)
	{
		cout << "Password have to contain more 8 and less 20 symbols.!"<< endl;
		return false;
	}
	for (int i = 0; i < pass.size(); i++)
	{
		if (islower(pass[i]) && !lower) {
			lower = true;
		}
		else if (isupper(pass[i]) && !upper) {
			upper = true;
		}
		else if (isdigit(pass[i]) && !digit) {
			digit = true;
		}
		else if (ispunct(pass[i]) && !punct) {
			punct = true;
		} if (lower && upper && digit && punct)
		{
			return true;
		}
	}
	cout << "Password have to contain at least one digit, lowercase and uppercase letters, and special symbol!" << endl;
	return false;
}
string generatePass() {
	string passWord;
	while (!isLegalPass(passWord))
	{
		passWord = "";
		int sizePass = 8 + rand() % 12;
		for (int i = 0; i < sizePass; i++)
		{
			char symbol = 33 + rand() % 93;
			passWord.push_back(symbol);
		}
	}
	return passWord;
}
string encrypt(string& toEncrypt) {
	string output;
	int key2 = 33 + rand() % 40;
	int key3= 33 + rand() % 40;
	for (int i = 0; i < toEncrypt.size(); i++)
	{
		int key1 = 1 + rand() % 4;
		output.push_back(toEncrypt[i] + key1);
		output.push_back(char(key1 + key2+key3));
	}
	output.push_back(char(key3));
	output.push_back(char(key2));
	return output;
}
string decrypt(string& toDecrypt) {
	string output;
	vector<int> keys;
	int key1 = int(toDecrypt[toDecrypt.size() - 1]);
	int key2 = int(toDecrypt[toDecrypt.size() - 2]);
	for (int i = 1; i < toDecrypt.size() - 1; i = i + 2)
	{
		output.push_back(toDecrypt[i - 1] - (toDecrypt[i] - key1-key2));
	}
	return output;
}