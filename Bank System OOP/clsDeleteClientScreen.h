#pragma once
#include<iostream>
#include <iomanip>
#include"clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen:protected clsScreen
{
private:

	static void _Print(clsBankClient Client) {
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
	static void ShowDeleteClientScreen() {
		if (!CheckAccessRight(clsUser::enPermissions::pDeleteClient)) {
			return;
		}

		clsScreen::_DrawScreenHeader("\t Delete Client screen");
	
		cout << "\nEnter account number for client? ";
		string accountnum;

		accountnum = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(accountnum)) {
			cout << "\nEnter valid account number? ";
			accountnum = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(accountnum);
		_Print(client);
		cout << "Are You Suer You Want To Delete This Client? Y/N? ";
		char confirm;
		cin >> confirm;
		if (toupper(confirm) == 'Y') {
			if (client.Delete()) {
				cout << "\nAccount Deleted Successfully :-)\n";
				_Print(client);
			}
			else
				cout << "\nError Account Was not Deleted";
		}
	}
};

