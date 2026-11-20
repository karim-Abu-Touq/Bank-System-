#pragma once
#include<iostream>
#include <iomanip>
#include"clsScreen.h"
#include "clsBankClient.h"
class clsTransferLogScreen:protected clsScreen
{
private:

    static void PrintTransferLogRecordLine(clsBankClient::StTransferLog TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.Date;
        cout << "| " << setw(8) << left << TransferLogRecord.AccountFrom;
        cout << "| " << setw(8) << left << TransferLogRecord.AccountTo;
        cout << "| " << setw(8) << left << TransferLogRecord.Ammount;
        cout << "| " << setw(10) << left << TransferLogRecord.SourceBalance;
        cout << "| " << setw(10) << left << TransferLogRecord.DestanationBalance;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName;


    }

public:
	static void ShowTransferLogScreen() {
		vector<clsBankClient::StTransferLog> vTransferList = clsBankClient::GetTransferLogsList();
        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferList.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferList.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else {
            for (clsBankClient::StTransferLog& T : vTransferList) {
                PrintTransferLogRecordLine(T);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};

