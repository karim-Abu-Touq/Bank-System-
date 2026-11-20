#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h"
#include"clsInputValidate.h"
class clsAddNewUserScreen:protected clsScreen
{private:
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
				permissions+=clsUser::enPermissions::pListClients;
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

	static void _ReadUserData(clsUser& User)  {
		cout << "Enter First name? ";
		User.FirstName=clsInputValidate::ReadString();
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
		User.Password= clsInputValidate::ReadString();
		cout << endl;

		User.Permissions = _ReadPermissionsToSet();
	
	}

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

	static void ShowAddNewUserScreen() {

		_DrawScreenHeader("\t Add New User Screen");

		cout << "Please enter user name? ";
		string username = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(username)) {
			cout << "\nThis User name already exist ,choose another one? ";
			username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::GetAddNewUserObject(username);
		_ReadUserData(User);

		clsUser::enSaveResult Result= User.Save();

		switch (Result) {
		case clsUser::enSaveResult::svFailedEmptyObject:
		    cout << "\nError User was not saved because it's Empty";
			break;


		case clsUser::enSaveResult::svFailedUserNameExist:
			cout << "\nError User was not saved because UserName is used!\n";
			break;


		case clsUser::enSaveResult::svSucceded:
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(User);
			break;


		}


	}
};

