#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h"
#include"clsInputValidate.h"
class clsDeleteUserScreen:protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}
public:

	static void ShowDeleteUserScreen() {

		_DrawScreenHeader("\t  Delete User Screen");

		string username;
		cout << "Please enter user name? ";
		username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(username)) {
			cout << "Please enter an exist user name? ";
			username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(username);
		_PrintUser(User);

		cout << "\nAre You Sure You Want To Delete This User? Y/N? ";
		char answer;
		cin >> answer;
		if (toupper(answer) == 'Y') {
			if (User.Delete()) {
				cout << "User Deleted Successfully :-)\n";
				_PrintUser(User);
			}
		}
		else
		{
			cout << "\nError User Was not Deleted\n";
		}

	}
};

