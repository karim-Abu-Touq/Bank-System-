#pragma once
#include<iostream>
#include <string>
#include<vector>
#include<fstream>
#include"clsPerson.h"
#include"clsString.h"
#include "clsDate.h"
#include "Global.h"
using namespace std;


class clsBankClient:public clsPerson
{

private:
	enum enMode{EmptyMode=0,UpdateMode=1,AddNewMode=2};

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line,string Seperator) {
		vector<string> vClientData = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5],stod( vClientData[6]));
	}


	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator) {
		string Line = "";
		Line += Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client._AccountNumber+ Seperator;
		Line += Client._PinCode + Seperator;
		Line += to_string(Client._AccountBalance);
		return Line;
	}


	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile() {
		vector<clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				vClients.push_back(_ConvertLineToClientObject(Line,"#//#"));
			}
			MyFile.close();
		}
		return vClients;
	}

	void _SaveClientsDataToFile(vector<clsBankClient> vClients) {
		string Line;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsBankClient& C : vClients) {
				if (!C._MarkForDelete) {
					Line = _ConvertClientObjectToLine(C, "#//#");
					MyFile << Line << endl;
				}
			}
			MyFile.close();
		}
	}
	void _AddDataLineToFile(string Line) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app);
		if (MyFile.is_open()) {
			MyFile << Line << endl;
		}
		MyFile.close();
	}


	void _Update() {
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : vClients) {
			if (C.GetAccountNumber() == _AccountNumber)
				C = *this;
		}
		_SaveClientsDataToFile(vClients);

	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this,"#//#"));
	}

	struct StTransferLog;
	string _ConvertTransferLogToLine(clsBankClient DestClient,double Ammount,string Seperator="#//#") {
		string Line = "";
		Line += clsDate::GetSystemDateTimeString() + Seperator;
		Line += GetAccountNumber() + Seperator;
		Line += DestClient.GetAccountNumber() + Seperator;
		Line += to_string(Ammount) + Seperator;
		Line += to_string(AccountBalance) + Seperator;
		Line += to_string(DestClient.AccountBalance) + Seperator;
		Line += CurrentUser.UserName;
		return Line;
	}
	static StTransferLog _ConvertLineToTransferLog(string Line, string Seperator = "#//#") {
		vector<string> vTransferDate = clsString::Split(Line, Seperator);
		StTransferLog TransferData;
		TransferData.Date = vTransferDate[0];
		TransferData.AccountFrom = vTransferDate[1];
		TransferData.AccountTo = vTransferDate[2];
		TransferData.Ammount = stod(vTransferDate[3]);
		TransferData.SourceBalance = stod(vTransferDate[4]);
		TransferData.DestanationBalance = stod(vTransferDate[5]);
		TransferData.UserName = vTransferDate[6];
		return TransferData;
	}
	static vector<StTransferLog> _LoadTransferLogFromFile() {
		vector<StTransferLog> VTransferLogs;
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				VTransferLogs.push_back(_ConvertLineToTransferLog(Line));
			}
			MyFile.close();
		}
		return VTransferLogs;
	}

public:

	struct StTransferLog
	{
		string Date;
		string AccountFrom;
		string AccountTo;
		double Ammount;
		double SourceBalance;
		double DestanationBalance;
		string UserName;
	};

	clsBankClient( enMode Mode,string FirstName, string LastName, string Email, string Phone,string AccountNumber, string PinCode, float AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_AccountNumber=AccountNumber;
		 _PinCode=PinCode;
		 _AccountBalance=AccountBalance;
	}
	
	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {
		return(_Mode == enMode::EmptyMode);
	}
	string GetAccountNumber() {
		return _AccountNumber;
	}
	string GetPinCode() {
		return _PinCode;
	}
	float GetAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;

	

	static clsBankClient Find(string AccountNumber) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line,"#//#");
				if (Client._AccountNumber == AccountNumber) {
					MyFile.close();
					return Client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber,string PinCode) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");
				if (Client._AccountNumber == AccountNumber && Client._PinCode==PinCode) {
					MyFile.close();
					return Client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = Find(AccountNumber);
		return(!Client.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNum) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNum, "", 0);
	}
	bool Delete() {
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : vClients) {
			if (C.GetAccountNumber() == _AccountNumber) {
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}
	static vector<clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances() {
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();
		double TotalBalances = 0;
		for (clsBankClient& Client : vClients) {
			TotalBalances += Client._AccountBalance;
		}
		return TotalBalances;
	}

	enum enSaveResult{svFailedEmptyObject=0,svSucceded=1, svFailedAccountNumExist=2};
    enSaveResult Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode:
			if(IsEmpty())
			 return enSaveResult::svFailedEmptyObject;
			
		case enMode::UpdateMode:
			_Update();
			return enSaveResult::svSucceded;
			break;

		case enMode::AddNewMode:
			if (IsClientExist(_AccountNumber))
				return enSaveResult::svFailedAccountNumExist;
			else {
				_AddNew();
				return enSaveResult::svSucceded;
			}
			break;
	
		}

		
	}
	void Deposit(double Ammount) {
		AccountBalance += Ammount;
		Save();
	}
	void Withdraw(double Ammount) {
		AccountBalance -= Ammount;
		Save();
	}

	void RegisterTransfer(clsBankClient& DestenationClient, double Ammount) {
		string Line = _ConvertTransferLogToLine(DestenationClient, Ammount);
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << Line << endl;
		}
		MyFile.close();
	
	}
	bool Transfer(clsBankClient& DestenationClient, double Ammount) {
		if (Ammount > AccountBalance) {
			return false;
		}
		else {
			Withdraw(Ammount);
			DestenationClient.Deposit(Ammount);
			RegisterTransfer(DestenationClient, Ammount);
			return true;
		}
	}
	static vector<StTransferLog> GetTransferLogsList() {
		return _LoadTransferLogFromFile();
	}







};

