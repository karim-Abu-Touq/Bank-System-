#pragma once
#include<iostream>
#include <iomanip>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include "clsListUserScreen.h"
#include"clsAddNewUserScreen.h"
#include"clsDeleteUserScreen.h"
#include"clsUpdateUserScreen.h"
#include"ClsFindUserScreen.h"
class clsManageUsersScreen:protected clsScreen
{
private:
	enum enManageUsersMenueOptions{ListUsers=1,AddNewUser=2,DeleteUser=3,UpdateUser=4,FindUser=5,MainMenue=6}; 

	static short _ReadManageUsersOption() {
		cout << setw(37) << left << "" << "Choose What Do You Want To DO? [1-6]? ";
		short Option =clsInputValidate::ReadIntNumBetween(1, 6, "Choose Option Between 1 and 6? ");
		return Option;
	
	} 

	static void _GoBackToManageUsersMenue() {
		cout << setw(37) << left << "" << "\n\tPress Any Key To Go Back To Manage Users Menue...\n";
		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _ShowAllUsersScreen() {
		clsListUserScreen::ShowUsersListScreen();
	}

	static void _ShowAddNewUserScreen() {
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen() {
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen() {
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen() {
		ClsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUserOption) {
		switch (ManageUserOption) {
		case enManageUsersMenueOptions::ListUsers:
			system("cls");
			_ShowAllUsersScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersMenueOptions::AddNewUser:
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersMenueOptions::DeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersMenueOptions::UpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersMenueOptions::FindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenue();
			break;

		case enManageUsersMenueOptions::MainMenue:{
			
			}


		}
	}

public:
	static void ShowManageUsersMenue() {

		system("cls");
		if (!CheckAccessRight(clsUser::enPermissions::pManageUsers)) {
			return;
		}
		_DrawScreenHeader("\t Manage Users Screen");
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t Manage Users Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PerformManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersOption());
	}
};

