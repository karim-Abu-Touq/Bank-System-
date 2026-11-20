#pragma once
#include<iostream>
#include <iomanip>
#include"clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsDepositScreen :protected clsScreen
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
	static void ShowDepositScreen() {
		_DrawScreenHeader("\t Deposite Screen");

		cout << "\nEnter account number for client? ";
		string accountnum = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accountnum)) {
			cout << "\nEnter valid account number? ";
			accountnum = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(accountnum);
		_PrintClient(Client);

		double DepositAmmount = 0;
		cout << "Please Enter Deposit Ammount? ";
		 DepositAmmount= clsInputValidate::ReadDblNum();

		 while (DepositAmmount < 0) {
			 cout << "please enter positive number? ";
			 DepositAmmount = clsInputValidate::ReadDblNum();
		 }

		 cout << "Are you sure you want to perform this transaction? ";
		 char confirm;
		 cin >> confirm;
		 if (toupper(confirm) == 'Y') {
			 Client.Deposit(DepositAmmount);
			 cout << "Ammount Deposited successfully :-)\n";
			 cout << "Your Account Balance Now is " << Client.AccountBalance << endl;
		 }
	}
};

