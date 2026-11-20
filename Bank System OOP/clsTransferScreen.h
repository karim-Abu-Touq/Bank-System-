#pragma once
#include<iostream>
#include <iomanip>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include "clsBankClient.h"
class clsTransferScreen:protected clsScreen
{
private:
	static void _PrintClientCard(clsBankClient Client) {
		cout << "\nClient Card:\n";
		cout << "----------------------------------\n";
		cout << "Full Name    : " << Client.FullName() << endl;
		cout << "Acc. Number  : " << Client.GetAccountNumber() << endl;
		cout << "Balance      : " << Client.AccountBalance << endl;
		cout << "----------------------------------\n";
	}

	static string _ReadAccountNumber() {
		string Acc_num = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(Acc_num)) {
			cout << "\nPlease Enter An Exist Account number ? ";
			Acc_num = clsInputValidate::ReadString();
		}
		return Acc_num;
	}

	static double _ReadAmmount(clsBankClient SourceClient) {
		cout << "Enter Tansfer Ammount? ";
		double Ammount = clsInputValidate::ReadDblNumBetween(0, SourceClient.AccountBalance,
			"Ammount Exceeds The Available Balance , Enter Another Ammount? ");
		return Ammount;
	}

public:
	static void ShowTransferScreen() {
		_DrawScreenHeader("\t\tTransferScreen");
		
		cout << "\nPlease Enter Account number To Transfer From? ";
		string Acc_num1 = _ReadAccountNumber();
		clsBankClient SourceClient = clsBankClient::Find(Acc_num1);
		_PrintClientCard(SourceClient);

		cout << "\nPlease Enter Account number To Transfer To? ";
		string Acc_num2 = _ReadAccountNumber();
		clsBankClient DestanationClient = clsBankClient::Find(Acc_num2);
		_PrintClientCard(DestanationClient);

		double Ammount = _ReadAmmount(SourceClient);
		
		cout << "Are You Sure You Want To Perform This Operation? Y/N? ";
		char answer;
		cin >> answer;
		if (toupper(answer) == 'Y') {
			if (SourceClient.Transfer(DestanationClient, Ammount))
				cout << "The Transfer Succedded :-) \n";
			else
				cout << "The Transfer Failed :-( \n";
		}
		else {
			cout << "The Transfer Failed :-( \n";
		}
		_PrintClientCard(SourceClient);
		_PrintClientCard(DestanationClient);


	}
};

