#pragma once
#include<iostream>
#include <iomanip>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsUpdateClientScreen.h"
#include"clsFindClientScreen.h"
#include"clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include"clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"
#include"Global.h"
class clsMainScreen:protected clsScreen
{
private:
	enum enMainMenueOptions{eListClients=1 ,eAddClient=2 ,eDeleteClient=3,
		eUpdateClient=4 ,eFindClient=5 ,eTransactions=6,
		eManageUsers=7,eLoginRegister=8,eCurrencyExchange=9,eExit=10};
	static short _ReadMainMenueOption() {
		cout << setw(37) << left << "" << "Choose what Do You Want To Do? [1-10]? ";
		short Option = clsInputValidate::ReadIntNumBetween(1, 10, "Enter Number Between 1 to 10");
		return Option;
	}
	static void _GoBackToMainMenue() {
		cout << setw(37) << left << "" << "\n\tPress Any Key To Go Back To Main Menue...\n";
		system("pause>0");
		ShowMainMenue();
	}
	static void _ShowAllClientsScreen() {
		clsClientListScreen::ShowClientListScreen();
	}
	static void _ShowAddNewClientScreen() {
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}
	static void _ShowDeleteClientScreen() {
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}
	static void _ShowUpdateClientScreen() {
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}
	static void _ShowFindClientScreen() {
		clsFindClientScreen::ShowFindClientScreen();
	}
	static void _ShowTransactionMenue() {
		clsTransactionsScreen::ShowTransactionMenue();
	}
	static void _ShowManageUsersMenue() {
		clsManageUsersScreen::ShowManageUsersMenue();
	}
	static void _ShowLoginRegisterScreen() {
		clsLoginRegisterScreen::ShowLoginRedisterScreen();
	}
	static void _ShowCurrencyExchangeScreen() {
		clsCurrencyExchangeScreen::ShowCurrenciesMenue();
	}

	static void _Logout() {
		CurrentUser = clsUser::Find("", "");
	}

	static void PerformMainMenueOption(enMainMenueOptions MainMenueOption) {
		switch (MainMenueOption) {
		case enMainMenueOptions::eListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
			
		case enMainMenueOptions::eAddClient:
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
	
		case enMainMenueOptions::eTransactions:
			system("cls");
			_ShowTransactionMenue();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eManageUsers:
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break;


		case enMainMenueOptions::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eExit:
			system("cls");
			_Logout();
			//login()
			break;
		}

	}

public:
	static void ShowMainMenue() {
		system("cls");
		_DrawScreenHeader("\t\t\Main Screen");
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client .\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		PerformMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());

	}
};

