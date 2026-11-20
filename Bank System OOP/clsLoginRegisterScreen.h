#pragma once
#include<iostream>
#include <iomanip>
#include"clsUser.h"
#include"clsScreen.h"
class clsLoginRegisterScreen:protected clsScreen
{

private:

	static void PrintLoginRegisterRecordLine(clsUser::stLoginRegisterDetails LoginRegisterRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.Date;
		cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
		cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
		cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
	}


public:
	static void ShowLoginRedisterScreen() {
		if (!CheckAccessRight(clsUser::enPermissions::pLoginRegisters)) {
			return;
		}

		vector<clsUser::stLoginRegisterDetails> vLoginRegesters = clsUser::GetLoginRegistersList();

		string Title = "\tLogin Register List Screen";
		string SubTitle = "\t\t(" + to_string(vLoginRegesters.size()) + ") Record(s)";
		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		
		if (vLoginRegesters.size() == 0) {
			cout << "\t\t\t\tNo Logins Available In the System!";
		}
		else
		{
			for (clsUser::stLoginRegisterDetails& L : vLoginRegesters) {
				PrintLoginRegisterRecordLine(L);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};

