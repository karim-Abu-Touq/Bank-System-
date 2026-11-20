#pragma once
#include<iostream>
#include"clsDate.h"
using namespace std;

class clsInputValidate
{
public:
	static bool IsNumberBetween(short num, short start, short end) {
		return (num >= start && num <= end) ? true : false;
	}
	static bool IsNumberBetween(int num, int start, int end) {
		return (num >= start && num <= end) ? true : false;
	}
	static bool IsNumberBetween(float num, float start, float end) {
		return (num >= start && num <= end) ? true : false;
	}
	static bool IsNumberBetween(double num, double start, double end) {
		return (num >= start && num <= end) ? true : false;
	}

	static bool IsDateBetween(clsDate date, clsDate date1, clsDate date2) {
		if (clsDate::IsDate1AfterDate2(date1, date2)) {
			clsDate temp = date1;
			date1 = date2;
			date2 = temp;
		}
		if ((clsDate::IsDate1AfterDate2(date, date1) && clsDate::IsDate1LessThanDate2(date, date2)) || clsDate::IsDate1EqualDate2(date, date1) || clsDate::IsDate1EqualDate2(date, date2))
			return true;
		else
			return false;
	}

	static int ReadIntNum(string errorMessage = "Invalid Number, Enter again\n") {
		int x;
		while (!(cin >> x)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << errorMessage;
		}
		return x;
	}
	static double ReadDblNum(string errorMessage = "Invalid Number, Enter again\n") {
		double x;
		while (!(cin >> x)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << errorMessage;
		}
		return x;
	}

	static int ReadIntNumBetween(int start, int end, string errorMessage = "Number is not within range, Enter again : \n") {
		int x = ReadIntNum();
		while (!IsNumberBetween(x, start, end)) {
			cout << errorMessage << "? ";
			x = ReadIntNum(errorMessage);
		}
		return x;
	}

	static double ReadDblNumBetween(double start, double end, string errorMessage = "Number is not within range, Enter again : \n") {
		double x = ReadDblNum();
		while (!IsNumberBetween(x, start, end)) {
			cout << errorMessage << "? ";
			x = ReadDblNum(errorMessage);
		}
		return x;
	}

	static bool IsValidDate(clsDate date) {
		return date.IsValidDate();
	}
	static string ReadString()
	{
		string  S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}
};

