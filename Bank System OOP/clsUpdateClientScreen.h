#pragma once
#include<iostream>
#include <iomanip>
#include"clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsUpdateClientScreen:protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& client) {

		cout << "\nEnter First name? ";
		client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last name? ";
		client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email? ";
		client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone? ";
		client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password? ";
		client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance? ";
		client.AccountBalance = clsInputValidate::ReadDblNum();
	}
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
	static void ShowUpdateClientScreen() {

		if (!CheckAccessRight(clsUser::enPermissions::pUpdateClients)) {
			return;
		}

		_DrawScreenHeader("\t Update Info screen");


		cout << "\nEnter account number for client? ";
		string accountnum = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accountnum)) {
			cout << "\nEnter valid account number? ";
			accountnum = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::Find(accountnum);
		_PrintClient(client);

		_ReadClientInfo(client);

		clsBankClient::enSaveResult Result = client.Save();

		switch (Result) {
		case clsBankClient::enSaveResult::svFailedEmptyObject:
			cout << "\nError, Account Was not Save Because it is Empty\n";
			break;
		case clsBankClient::enSaveResult::svSucceded:
			cout << "\nAccount Update Successfully :-)\n";
			_PrintClient(client);

		}
	}
};

