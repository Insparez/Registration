// Registration app
// Developed by inspare
#include "Account.h"

map<string, string> accounts;


int main()
{
	//system("color F0");
	srand(time(0));
	string nickName, passWord;
	ofstream fout;
	fout.open("Accounts.txt", ofstream::app);
	fout.close();
	bool isAccounts = parceFile(accounts);
	//start 
	while (true)
	{
	if (whatToDo())
	{
		system("cls");
		bool isWrong = true;
		while (isWrong)
		{
			if (!isAccounts)
			{
				cerr << "\aNo accounts in database!" << endl;
				break;
			}
			inputFields(nickName, passWord, true);
			auto it = accounts.find(nickName);
			if (it != accounts.end() && passWord == decrypt(it->second))
			{
				cout << "\nSuccsesfully login in account!\n" << endl;
				isWrong = false;
				accMenu(it);
				system("cls");
			}
			else {
				cout << "\n\aWrong name or password!";
			}
		}
	}
	else {
		system("cls");
		showRules();
		inputFields(nickName, passWord);
		while (accounts.count(nickName))
		{
			cout << "\aSorry name is occupied." << endl;
			inputFields(nickName, passWord);
		}
		writeToFile(nickName, encrypt(passWord), isAccounts);
	}

	}
	//end
	system("pause");
}
