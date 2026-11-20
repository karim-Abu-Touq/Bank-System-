#pragma once
#include<iostream>
#include <string>
#include<vector>
#include<fstream>
#include"clsPerson.h"
#include"clsString.h"
#include "clsUtil.h"
class clsUser:public clsPerson
{
private:
	enum enMode{EmptyMode=0,UpdateMode=1,AddNewMode=2};

	string _UserName;
	string _Password;
	int _Permissions;
	enMode _Mode;

	bool _MarkedForDelete = false;

   

	static clsUser _ConvertLineToUserObject(string Line, string Seperator) {
		vector<string> vUserData = clsString::Split(Line, Seperator);
		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4],
			clsUtil::DecryptText (vUserData[5],2), stoi(vUserData[6]));
	}
	static string _ConvertUserObjectToLine(clsUser User, string Seperator) {
		string Line = "";
		Line += User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User.UserName + Seperator;
		Line += clsUtil::EncryptText(User.Password, 2) + Seperator;
		Line += to_string(User._Permissions);
		return Line;
	}

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsUser> _LoadUsersDataFromFile() {
		vector<clsUser> vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				vUsers.push_back(_ConvertLineToUserObject(Line, "#//#"));
			}
			MyFile.close();
		}
		return vUsers;
	}
	static void _SaveUsersDataToFile(vector<clsUser> VUsers) {
		string Line;
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsUser& U : VUsers) {
				if (!U._MarkedForDelete) {
					Line = _ConvertUserObjectToLine(U, "#//#");
					MyFile << Line << endl;
				}
			}
			MyFile.close();
		}
	}
	void _AddDataLineToFile(string Line) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::app);
		if (MyFile.is_open()) {
			MyFile << Line << endl;
		}
		MyFile.close();
	}
    void _Update() {
		vector<clsUser> vUsers = _LoadUsersDataFromFile();
		for (clsUser& U : vUsers) {
			if (U.UserName == UserName)
			{
				U = *this;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);

	}
    void _AddNew() {
		_AddDataLineToFile(_ConvertUserObjectToLine(*this, "#//#"));
	}

    string _PrepareLoginRecord(string Seperator="#//#") {
		string Line = "";
		Line += clsDate::GetSystemDateTimeString() + Seperator;
		Line += UserName + Seperator;
		Line += clsUtil::EncryptText(Password,2) + Seperator;
		Line += to_string(Permissions);
		return Line;
	}
	
    struct stLoginRegisterDetails;

    static   stLoginRegisterDetails _ConvertLineToLoginRegisterStruct(string Line, string Seperator = "#//#") {
		 vector<string> vRegisterData = clsString::Split(Line, Seperator);
		 stLoginRegisterDetails LoginStruct;
		 LoginStruct.Date = vRegisterData[0];
		 LoginStruct.UserName = vRegisterData[1];
		 LoginStruct.Password = clsUtil::DecryptText( vRegisterData[2],2);
		 LoginStruct.Permissions = stoi(vRegisterData[3]);
		 return LoginStruct;
	 }

    static vector<stLoginRegisterDetails> _LoadRegistersDataFromFile() {
		 vector<stLoginRegisterDetails> vRegisters;
		 fstream MyFile;
		 MyFile.open("LoginRegister.txt", ios::in);
		 if (MyFile.is_open()) {
			 string Line;
			 while (getline(MyFile, Line)) {
				 vRegisters.push_back(_ConvertLineToLoginRegisterStruct(Line));
			 }
			 MyFile.close();
		 }
		 return vRegisters;
	 }
	 

public:
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegisters = 128
	
	};

	clsUser(enMode Mode,string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone) {
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
		_Mode = Mode;
	}

	void SetUserName(string UserName) {
		_UserName = UserName;
	}
	void SetPassword(string Password) {
		_Password = Password;
	}
	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}

	string GetUserName() {
		return _UserName;
	}
	string GetPassword() {
		return _Password;
	}
	int GetPermissions() {
		return _Permissions;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	bool IsEmpty() {
		return (_Mode==enMode::EmptyMode);
	}

	static clsUser Find(string UserName) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line, "#//#");
				if (User.UserName == UserName) {
					MyFile.close();
					return User;
				}

			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}
	static clsUser Find(string UserName,string Password) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToUserObject(Line, "#//#");
				if (User.UserName == UserName &&User.Password==Password) {
					MyFile.close();
					return User;
				}

			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName) {
		clsUser User = Find(UserName);
		return(!User.IsEmpty());
	}

	static bool IsUserExist(string UserName,string Password) {
		clsUser User = Find(UserName,Password);
		return(!User.IsEmpty());
	}


	static clsUser GetAddNewUserObject(string UserName) {
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}
    bool Delete() {
		vector<clsUser> vUsers = _LoadUsersDataFromFile();
		for (clsUser& U : vUsers) {
			if (U.UserName ==UserName) {
				U._MarkedForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}
	static vector<clsUser> GetUsersList() {
		return _LoadUsersDataFromFile();
	}

	enum enSaveResult { svFailedEmptyObject = 0, svSucceded = 1, svFailedUserNameExist=2 };
	enSaveResult Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode:
			if (IsEmpty())
				return enSaveResult::svFailedEmptyObject;

		case enMode::UpdateMode:
			_Update();
			return enSaveResult::svSucceded;
			break;

		case enMode::AddNewMode:
			if (IsUserExist(_UserName))
				return enSaveResult::svFailedUserNameExist;
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceded;
			}
			break;

		}


	}

	bool CheckAccessPermitions(enPermissions Permission) {
		if (this->Permissions == enPermissions::eAll)
			return true;
		else if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

   void RegesterLogin() {
	   string Line = _PrepareLoginRecord();
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << Line << endl;
		}
		MyFile.close();
	}

   struct stLoginRegisterDetails {
	   string Date;
	   string UserName;
	   string Password;
	   int Permissions;
   };
   static vector<stLoginRegisterDetails>GetLoginRegistersList() {
	   return _LoadRegistersDataFromFile();
   }
};

