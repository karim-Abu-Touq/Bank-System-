#pragma once
#include<iostream>
#include <iomanip>
#include"clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsWithdrawScreen:protected clsScreen
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
	static void ShowWithdrawScreen() {
		_DrawScreenHeader("\t Withdraw Screen");

		cout << "\nEnter account number for client? ";
		string accountnum = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accountnum)) {
			cout << "\nEnter valid account number? ";
			accountnum = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(accountnum);
		_PrintClient(Client);

		double WithdrawAmmount = 0;
		cout << "Please Enter Withdraw Ammount? ";
		WithdrawAmmount = clsInputValidate::ReadDblNumBetween(0,Client.AccountBalance,"Please enter a possitive ammount less than or equal account balance ");

		cout << "Are you sure you want to perform this transaction? Y/N? ";
		char confirm;
		cin >> confirm;
		if (toupper(confirm) == 'Y') {
			Client.Withdraw(WithdrawAmmount);
			cout << "Ammount Withdrawed successfully :-)\n";
			cout << "Your Account Balance Now is " << Client.AccountBalance << endl;
		}
	}
};

