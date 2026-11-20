#pragma once
#include<iostream>
#include <string>
#include"clsString.h"
#include<fstream>
using namespace std;
class clsCurrency
{
private:
	enum enMode{EmptyMode=0,UpdateMode=1};
	
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	double _Rate;

	static string _convertCurrencyObjectToLine(clsCurrency Currency,string Seperator="#//#") {
		string Line = "";
		Line += Currency.GetCountry() + Seperator;
		Line += Currency.GetCurrencyCode() + Seperator;
		Line += Currency.GetCurrencyName() + Seperator;
		Line += to_string(Currency.GetRate());
		return Line;
	}

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Sepeartor = "#//#") {
		vector<string> CurrencyData = clsString::Split(Line,Sepeartor);
		return clsCurrency(enMode::UpdateMode, CurrencyData[0], CurrencyData[1], CurrencyData[2], stod(CurrencyData[3]));

	}

	static vector<clsCurrency> _LoadCurrencyDataFromFile() {
		vector<clsCurrency> vCurrencyData;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line))
				vCurrencyData.push_back(_ConvertLineToCurrencyObject(Line));
			MyFile.close();
		}
		return vCurrencyData;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency>vCurrencies) {
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsCurrency& C : vCurrencies) {
				MyFile << _convertCurrencyObjectToLine(C) << endl;
			}
			MyFile.close();
		}

	}

	void _Update() {
		vector<clsCurrency> vCurrencies = _LoadCurrencyDataFromFile();
		for (clsCurrency& C : vCurrencies) {
			if (C.GetCurrencyCode() == GetCurrencyCode()) {
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}


public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, double Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	
	string GetCountry(){
		return _Country;
	}
	string GetCurrencyCode() {
		return _CurrencyCode;
	}
	string GetCurrencyName() {
		return _CurrencyName;
	}
	double GetRate() {
		return _Rate;
	}
	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}
	static vector <clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrencyDataFromFile();
	}

	static clsCurrency FindByCode(string CurrencyCode) {
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		vector <clsCurrency> vCurrencies = _LoadCurrencyDataFromFile();
		for (clsCurrency& C : vCurrencies) {
			if (C.GetCurrencyCode() == CurrencyCode) {
				return C;
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {
		Country = clsString::UpperAllString(Country);
		vector <clsCurrency> vCurrencies = _LoadCurrencyDataFromFile();
		for (clsCurrency& C : vCurrencies) {
			if (clsString::UpperAllString( C.GetCountry()) == Country) {
				return C;
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {
		clsCurrency C = clsCurrency::FindByCode(CurrencyCode);
		return(!C.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}
	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / GetRate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.GetCurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.GetRate());

	}




};

