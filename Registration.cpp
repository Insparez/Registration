#include "Account.h"

map<string, string> accounts;

int main()
{
	srand(time(0));
	bool isAcc = startMenu();
	bool isWrong = true; // продолжать запрашивать поля воода пока не будет введено верное
	string nickName{ "FIR" };
	string passWord;
	ofstream fout;
	fout.open("Accounts.txt", ofstream::app);
	fout.close();
	bool firstAcc = parceFile(accounts);
	if (firstAcc && isAcc)
	{
		cerr << "No accounts in database!. Create new account " << endl;
		isAcc = false;
	}
	if (isAcc)
	{
		while (isWrong)
		{
			inputFields(nickName, passWord, true);
			auto it = accounts.find(nickName);
			if (it != accounts.end() && passWord == decrypt(it->second))
			{
				cout << "\nSuccsesfully login in account!\n" << endl;
				isWrong = false;
				accMenu(it);
			}
			else {
				cout << "\nWrong name or password!" << endl;
			}
		}
	}
	else {
		inputFields(nickName, passWord);
		while (accounts.count(nickName))
		{
			cout << "Sorry name is occupied." << endl;
			inputFields(nickName, passWord);
		}
		writeToFile(nickName, encrypt(passWord), firstAcc);
	}
	system("pause");
}
