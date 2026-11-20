#pragma once
#include<iostream>
#include <iomanip>
#include"clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsFindClientScreen:protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client) {
		cout << "\nClient Card:";
		cout << "\n------------------------------------";
		cout << "\nFirstName    : " << Client.FirstName;
		cout << "\nLastName     : " << Client.LastName;
		cout << "\nFullName     : " << Client.FullName();
		cout << "\nEmail        : " << Client.Email;
		cout << "\nPhone        : " << Client.Phone;
		cout << "\nAcc. Number  : " << Client.GetAccountNumber();
		cout << "\nPassword     : " << Client.PinCode;
		cout << "\nBalance      : " << Client.AccountBalance;
		cout << "\n------------------------------------\n";
	}
public:
	static void ShowFindClientScreen() {
		if (!CheckAccessRight(clsUser::enPermissions::pFindClient)) {
			return;
		}

		_DrawScreenHeader("\t Find Client screen");


		cout << "\nEnter account number for client? ";
		string accountnum = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accountnum)) {
			cout << "\nAccount Number Was not Find, Choose another One? ";
			accountnum = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(accountnum);
		_PrintClient(Client);
	}
};

