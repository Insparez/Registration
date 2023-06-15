// Registration app
// Developed by inspare
#include "Account.h"

void showRules() {
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	sleepper("Rules for creating a nickname:");
	sleepper("-Nickname have to contain from 4 to 15 symbols;");
	sleepper("-Nickname can contains only a-z, A-Z, 0-9 and _ in the middle;");
	sleepper("-Name cant start with digit;");
	sleepper("-Nick doesnt contain only digits.");
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	sleepper("Rules for creating a password: ");
	sleepper("-Password have to contain more 8 and less 20 symbols;");
	sleepper("-Password have to contain at least one digit, lowercase and uppercase letters, and special symbol;");
	sleepper("-You can generate legit password, use letter 'g' in the password field.");
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	
}
void inputFields(string& nick, string& pass, bool isAcc) {
	if (!isAcc) // ���� ��� �������� �� ������ ��������� ��������
	{
		cout << "\nEnter your nickname: ";
		getline(cin >> ws, nick);
		while (accounts.count(nick))
		{
			cout << "\aThis name is occupied. " << endl;
			cout << "Enter your nickname: ";
			getline(cin >> ws, nick);
		}
		while (!isLegalName(nick)) {
			cout << "\aThe nickname does not match the requirements " << endl;
			cout << "Enter your nickname: ";
			getline(cin >> ws, nick);// ws ����� ��� ���� ����� ���������� �� ��������� �������� ����� cin � startmenu()
		}
		cout << "Enter your password: ";
		pass = inputPass();
		while (!isLegalPass(pass))
		{
			cout << "\n\aThe password does not match the requirements " << endl;
			cout << "Enter your password: ";
			pass = inputPass();
		}
	}
	else { // ���� ������� ���� �� ��� ������� ��� ������� �.� ������������ ������ ������� �����
		cout << "\nEnter your nickname: ";
		getline(cin >> ws, nick);
		cout << "Enter your password: ";
		pass = inputPass();
	}

}
void writeToFile(string nickName, string passWord, bool& isAccounts) {
	ofstream fout;
	fout.open("Accounts.txt", ofstream::app);
	if (fout.is_open())
	{
		if (!isAccounts) {
			fout << "-----------------------------\n" << nickName << "\n" << passWord << "\n-----------------------------" << endl;
			isAccounts = true;
		}
		else {
			fout << nickName << "\n" << passWord << "\n-----------------------------" << endl;
		}
		cout << "\nAccount succsesfully created!" << endl;
		accounts.insert(make_pair(nickName, passWord));
		
	}
	else {
		cerr << "\aSomtheing went wrong.";
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
		cerr << "\aError of openning the file, " << ex.what();
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
	for (auto i = acc.begin(), j = acc.begin(); i < acc.end(); i++)
	{
		if (distance(i, acc.end()) >= 4 && *i == "-----------------------------" && !(i + 1)->empty() && *(i + 1) != "-----------------------------" && !(i + 2)->empty() && *(i + 2) != "-----------------------------" && *(i + 3) == "-----------------------------")
		{
			j = i + 2;
			accounts.insert(make_pair(*(i + 1), *(j)));
			i += 2;
		}
		else {
			continue;
		}
	}
	fin.close();
	// ���������� � ���� ������ ��������� ���������
	overWritingToFile();
	//---------------------------------------------
	if (!accounts.size())
	{
		return false;
	}
	else {
		return true;
	}
}
bool isLegalName(string nickName) {
	if (nickName.size() < 4 || nickName.size() > 15)
	{
		return false;
	}
	bool onetimes = true;
	try
	{
		if (isdigit(nickName[0])) {

			return false;
		}
		else {
			long long a = stoll(nickName);

			return false;
		}
	}
	catch (const std::exception&)
	{
		for (int i = 0; i < nickName.size(); i++)
		{
			if (!isalnum(nickName[i]))
			{
				if (nickName[i] == '_' && i != 0 && i != nickName.size() - 1 && onetimes) // �������� ������� ������������� _ � ���� � � ���������x
				{
					onetimes = false;
					continue;
				}

				return false;
			}

		}
		return true;
	}
}
bool isLegalPass(string& pass) {
	bool lower = false;
	bool upper = false;
	bool digit = false;
	bool punct = false;
	if (pass == "g")
	{
		pass = generatePass();
		cout << "\nYour generated password: " << pass << endl;
		return true;
	}
	if (pass.size() < 8 || pass.size() > 20)
	{

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

	return false;
}
string inputPass()
{
	string pass = "";
	int ch = 0;
	while (true)
	{
		ch = _getch();
		if (ch >= 33 && ch <= 126) {
			cout << "*";
			pass += char(ch);
		}
		else if (ch == 13)
		{
			break;
		}
		else if (ch == 8 && !pass.empty())
		{
			cout << (char)8 << " " << (char)8;
			pass.erase(pass.size() - 1);
		}
	}
	return pass;
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
	int key3 = 33 + rand() % 40;
	for (int i = 0; i < toEncrypt.size(); i++)
	{
		int key1 = 1 + rand() % 4;
		output.push_back(toEncrypt[i] + key1);
		output.push_back(char(key1 + key2 + key3));
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
		output.push_back(toDecrypt[i - 1] - (toDecrypt[i] - key1 - key2));
	}
	return output;
}
void accMenu(map<string, string>::iterator it)
{
	cout << "Here's what you can do with your account, to do this, press: " << endl;
	cout << "Press 1 to delete your account" << endl;
	cout << "Press 2 to log out"<< endl;
	cout << "Press 3 to change name" << endl;
	cout << "Press ESC to quit" << endl;
	while (true)
	{
		char yn;
		//-- ��������� ����������� ������� ������������
		if (_kbhit())
		{
			std::cin.seekg(0, std::ios::end);
			std::cin.clear();
		}
		//--
		yn = _getch();
		if (yn == '1')
		{
			removeAcc(it);
			break;
		}
		else if (yn == '2') {

			break;
		}
		else if (yn == '3') {
			//changeName(it);
			break;
		}
		else if (yn == VK_ESCAPE)
		{
			exit(0);
		}
	}
}
void removeAcc(map<string, string>::iterator index)
{
	accounts.erase(index);
	overWritingToFile();
	cout << "\nAcoount deleted!." << endl;
}
void overWritingToFile()
{
	ofstream fout;
	fout.open("Accounts.txt");
	if (fout.is_open())
	{
		for (auto it = accounts.begin(); it != accounts.end(); ++it)
		{
			fout << "-----------------------------\n" << it->first << "\n" << it->second << endl;
		}
		if (accounts.size() != 0)
		{
			fout << "-----------------------------\n";
		}
	}
	else {
		cerr << "\aSomtheing went wrong.";
	}
	fout.close();
}
void sleepper(string s)
{
	int time = 0; //20
	for (int i = 0; i < s.length(); i++) {
		Sleep(time);
		cout << s[i];
	}
	cout << endl;
}
void updator()
{
	for (auto i = 0; i < 30; i++)
	{
		cout << (char)8 << " " << (char)8;
	}
}
bool whatToDo()
{
	cout << "Press 1 to create acoount"<< endl;
	cout << "Press 2 to login to your account"<< endl;
	cout << "Press ESC to quit"<< endl;
	char yn;
	while (true)
	{
		//-- ��������� ����������� ������� ������������
		if (_kbhit())
		{
			std::cin.seekg(0, std::ios::end);
			std::cin.clear();
		}
		//--
		yn=_getch();
		if (yn == '1')
		{
			return false;
		}
		else if (yn == '2') {

			return true;
		}
		else if (yn==VK_ESCAPE)
		{
			exit(0);
		} 
	}
}

//void changeName(map<string, string>::iterator index)
//{
//	*index->
//}



