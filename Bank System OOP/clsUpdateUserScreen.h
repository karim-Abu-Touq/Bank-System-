#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h"
#include"clsInputValidate.h"
class clsUpdateUserScreen:protected clsScreen
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
	static int _ReadPermissionsToSet() {
		char answer;
		int permissions = 0;
		cout << "\nDo You want Give This User Full Access? Y/N? ";
		cin >> answer;
		if (toupper(answer) == 'Y') {
			return -1;
		}
		else {
			cout << "\nDo You Want Give Access To:\n";
			cout << "\nShow Client List? Y/N? ";
			cin >> answer;
			if (toupper(answer) == 'Y') {
				permissions += clsUser::enPermissions::pListClients;
			}

			cout << "\nAdd New Client? Y/N? ";
			cin >> answer;
			if (toupper(answer) == 'Y') {
				permissions += clsUser::enPermissions::pAddNewClient;
			}

			cout << "\nDelete Client? Y/N? ";
			cin >> answer;
			if (toupper(answer) == 'Y') {
				permissions += clsUser::enPermissions::pDeleteClient;
			}

			cout << "\nUpdate Client? Y/N? ";
			cin >> answer;
			if (toupper(answer) == 'Y') {
				permissions += clsUser::enPermissions::pUpdateClients;
			}

			cout << "\nFind Client? Y/N? ";
			cin >> answer;
			if (toupper(answer) == 'Y') {
				permissions += clsUser::enPermissions::pFindClient;
			}

			cout << "\nTransactions Y/N? ";
			cin >> answer;
			if (toupper(answer) == 'Y') {
				permissions += clsUser::enPermissions::pTranactions;
			}

			cout << "\nManage Users? Y/N? ";
			cin >> answer;
			if (toupper(answer) == 'Y') {
				permissions += clsUser::enPermissions::pManageUsers;
			}

			cout << "\nShow Login Registers? Y/N? ";
			cin >> answer;
			if (toupper(answer) == 'Y') {
				permissions += clsUser::enPermissions::pLoginRegisters;
			}
			return permissions;
		}
	}
	static void _ReadUserData(clsUser& User) {
		cout << "Enter First name? ";
		User.FirstName = clsInputValidate::ReadString();
		cout << endl;

		cout << "Enter Last name? ";
		User.LastName = clsInputValidate::ReadString();
		cout << endl;

		cout << "Enter Email? ";
		User.Email = clsInputValidate::ReadString();
		cout << endl;

		cout << "Enter Phone number? ";
		User.Phone = clsInputValidate::ReadString();
		cout << endl;

		cout << "Enter Password? ";
		User.Password = clsInputValidate::ReadString();
		cout << endl;

		User.Permissions = _ReadPermissionsToSet();

	}
public:
	static void ShowUpdateUserScreen() {
		_DrawScreenHeader("\t  Update User Screen");

		string username;
		cout << "Please enter user name? ";
		username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(username)) {
			cout << "Please enter an exist user name? ";
			username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(username);
		_PrintUser(User);

		cout << "\nAre You Sure You Want To Update This User? Y/N? ";
		char answer;
		cin >> answer;
		if (toupper(answer) == 'Y') {
			_ReadUserData(User);
			clsUser::enSaveResult Result = User.Save();
			switch (Result) {

			case clsUser::enSaveResult::svFailedEmptyObject:
				cout << "\nError User was not Updated because it's Empty";
				break;

			case clsUser::enSaveResult::svSucceded:
				cout << "\nUser Updated Successfully :-)\n";
				_PrintUser(User);
				break;

			}
		}
		else
		{
			cout << "\nError User Was not Updated\n";
		}
	}
};

