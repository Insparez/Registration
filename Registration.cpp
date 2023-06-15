// Registration app
// Developed by inspare
#include "Account.h"

map<string, string> accounts;

int main()
{
	system("color F0");
	srand(time(0));
	string nickName, passWord;
	ofstream fout;
	fout.open("Accounts.txt", ofstream::app);
	fout.close();
	parceFile(accounts);
	//start 
	while (true)
	{
	if (whatToDo())
	{
		system("cls");
		bool isWrong = true;
		while (isWrong)
		{
			if (accounts.size()==0)
			{
				cerr << "\aNo accounts in database!";
				break;
			}
			inputFields(nickName, passWord, true);
			auto it = accounts.find(nickName);
			if (it != accounts.end() && passWord == decrypt(it->second))
			{
				system("cls");
				cout << "Succsesfully login in account!";
				isWrong = false;
				accMenu(it);
				
			}
			else {
				system("cls");
				cout << "\aWrong name or password!"<< endl;
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
		writeToFile(nickName, encrypt(passWord));
	}

	}
	//end
	system("pause");
}
