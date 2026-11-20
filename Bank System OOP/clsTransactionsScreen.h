#pragma once
#include<iostream>
#include <iomanip>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalancesScreen.h"
#include"clsTransferScreen.h"
#include"clsTransferLogScreen.h"
class clsTransactionsScreen :protected clsScreen
{
private:
	enum enTransactionOptions{Deposit=1,Withdraw=2,TotalBalances=3,Transfer=4,TransferLog=5,MainMenue=6};
	static short _ReadTransactionOptions() {
		cout << setw(37) << left << "" << "Choose what Do You Want To Do? [1-6]? ";
		short Option = clsInputValidate::ReadIntNumBetween(1, 6, "Enter Number Between 1 to 5");
		return Option;
	}
	static void _GoBackToTransactionsMenue() {
		cout << setw(37) << left << "" << "\n\tPress Any Key To Go Back To Main Menue...\n";
		system("pause>0");
		ShowTransactionMenue();
	}

	static void _ShowDepositScreen() {
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen() {
		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen() {
		clsTotalBalancesScreen::ShowTotalBalances();
	}
	static void _ShowTransferScreen() {
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void PerformTransactionsMenueOption(enTransactionOptions TransactionOption) {
		switch (TransactionOption) {
		case enTransactionOptions::Deposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;

		case enTransactionOptions::Withdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;

		case enTransactionOptions::TotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;

		case enTransactionOptions::Transfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;

		case enTransactionOptions::TransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
			break;

		case enTransactionOptions::MainMenue:
		{
		
		}
		}
		
	}
	


	

public:
	static void ShowTransactionMenue() {
		if (!CheckAccessRight(clsUser::enPermissions::pTranactions)) {
			return;
		}

		system("cls");
		_DrawScreenHeader("\t  TransActions Screen");
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tTransactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		PerformTransactionsMenueOption((enTransactionOptions)_ReadTransactionOptions());
	}
	
};

