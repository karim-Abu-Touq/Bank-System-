#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h"
#include"clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen:protected clsScreen
{private:
	
	static bool _Login() {
		short trials = 0;
		bool LoginFailed = false;

		do {
			if (LoginFailed) {
				trials++;
				cout << "Invalid username/password , retry: \n";
				cout << "you have " << 3-trials << " trials to login.\n\n";
			}


			if (trials == 3) {
				cout << "You are locked after 3 failes trials\n";
				return false;
			}
			string username, password;
			cout << "Enter username? ";
			cin >> username;
			cout << "Enter Password? ";
			cin >> password;

			CurrentUser = clsUser::Find(username, password);
			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);
		CurrentUser.RegesterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	

	}



public:
	static bool ShowLoginScreen() {
		_DrawScreenHeader("\t     Login Screen");
		return _Login();
		

	}
};

