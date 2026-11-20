#pragma once
#include <ctime>  
#include<iostream>
#include <string>  
#include <vector>


using namespace std;

#pragma warning(disable :4996);
class clsDate
{
private:
	short _Day;
	short _Month;
	short _Year;

public:
	void SetDay(short Day) {
		_Day = Day;
	}
	void SetMonth(short Month) {
		_Month = Month;
	}
	void SetYear(short Year) {
		_Year = Year;
	}

	short GetDay() {
		return _Day;
	}
	short GetMonth() {
		return _Month;
	}
	short GetYear() {
		return _Year;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;
	__declspec(property(get = GetYear, put = SetYear)) short Year;



	void ConvertStringDatetoObjectDate(string sDate) {
		vector<string> vDate;
		string word = "";

		for (int i = 0; i < sDate.length(); i++) {
			if (sDate[i] != '/')
				word += sDate[i];
			else {
				vDate.push_back(word);
				word = "";
			}
		}
		if (word != "")
			vDate.push_back(word);
		if (vDate.size() == 3) {
			_Day = stoi(vDate[0]);
			_Month = stoi(vDate[1]);
			_Year = stoi(vDate[2]);
		}
		else
			cout << "invalid" << endl;

	}

	static bool IsLeapYear(int Year) {
		return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0));
	}
	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}

	static int NumOfDaysInMonth(int Month, int Year) {
		if (Month < 1 || Month>12)
			return 0;
		int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : days[Month - 1];
	}
	int NumOfDaysInMonth() {
		return NumOfDaysInMonth(_Month, _Year);
	}

	static string GetDateFromNumOfDays(int Days, int Year) {

		int month = 1;
		while (Days > NumOfDaysInMonth(month, Year)) {

			Days -= NumOfDaysInMonth(month, Year);
			month++;

		}
		string Date = to_string(Days) + "/" + to_string(month) + "/" + to_string(Year);
		return Date;

	}
	string GetDateFromNumOfDays(int Days) {
		return GetDateFromNumOfDays(Days, _Year);
	}

	bool IsValidDate(short Day, short Month, short Year) {
		if (Year < 1)
			return false;
		if (Month > 12 || Month < 1)
			return false;
		if (Day<1 || Day > NumOfDaysInMonth(Month, Year))
			return false;
		return true;
	}
	bool IsValidDate() {
		return IsValidDate(_Day, _Month, _Year);
	}

	static int NumOfDaysInYear(int Year) {
		return (IsLeapYear(Year)) ? 366 : 365;
	}
	int NumOfDaysInYear() {
		return NumOfDaysInYear(_Year);
	}

	static int CalculateDays(int Day, int Month, int Year) {
		int sumofdays = Day;
		for (int i = 1; i < Month; i++) {
			sumofdays += NumOfDaysInMonth(i, Year);
		}
		return sumofdays;
	}
	int CalculateDays() {
		return CalculateDays(_Day, _Month, _Year);
	}

	static bool IsDate1LessThanDate2(clsDate& Date1, clsDate& Date2) {
		return (Date1._Year < Date2._Year) ? true :
			(Date1._Year == Date2._Year && (CalculateDays(Date1._Day, Date1._Month, Date1._Year) < CalculateDays(Date2._Day, Date2._Month, Date2._Year)) ? true : false);
	}
	bool IsLessThanDate(clsDate Date) {
		return IsDate1LessThanDate2(*this, Date);
	}

	static bool IsDate1EqualDate2(clsDate& Date1, clsDate& Date2) {
		return (Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day == Date2._Day) ? true : false;
	}
	bool IsEqualDate(clsDate Date) {
		return IsDate1EqualDate2(*this, Date);
	}

	static bool IsDate1AfterDate2(clsDate& Date1, clsDate& Date2) {
		return !(IsDate1LessThanDate2(Date1, Date2) || IsDate1EqualDate2(Date1, Date2));
	}
	bool IsAfterDate(clsDate Date) {
		return IsDate1AfterDate2(*this, Date);
	}

	static int CompareDate(clsDate& Date1, clsDate& Date2) {
		return((IsDate1LessThanDate2(Date1, Date2)) ? -1 : (IsDate1EqualDate2(Date1, Date2) ? 0 : 1));
	}
	int CompareDate(clsDate Date) {
		return CompareDate(*this, Date);
	}

	static bool IsLastDayInMonth(clsDate& Date) {
		int days = NumOfDaysInMonth(Date._Month, Date._Year);
		return (days == Date._Day) ? true : false;
	}
	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(clsDate& Date) {
		return (Date._Month == 12) ? true : false;
	}
	bool IsLastMonthInYear() {
		return IsLastMonthInYear(*this);
	}

	static clsDate IncreaseDateByOne(clsDate& Date) {

		if (IsLastDayInMonth(Date)) {
			if (IsLastMonthInYear(Date)) {
				Date._Day = 1;
				Date._Month = 1;
				Date._Year++;
			}
			else {
				Date._Day = 1;
				Date._Month++;
			}
		}
		else
			Date._Day++;
		return Date;

	}
	void IncreaseDateByOne() {
		*this = IncreaseDateByOne(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date, int Days) {
		for (int i = 1; i <= Days; i++) {
			Date = IncreaseDateByOne(Date);
		}
		return Date;
	}
	void IncreaseDateByXDays(int Days) {
		*this = IncreaseDateByXDays(*this, Days);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date) {
		Date = IncreaseDateByXDays(Date, 7);
		return Date;
	}
	void IncreaseDateByOneWeek() {
		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate& Date, int Weeks) {

		return IncreaseDateByXDays(Date, Weeks * 7);
	}
	void IncreaseDateByXWeeks(int Weeks) {
		*this = IncreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date) {
		if (IsLastMonthInYear(Date)) {
			Date._Month = 1;
			Date._Year++;
		}
		else {
			Date._Month++;
			if (Date._Day > NumOfDaysInMonth(Date._Month, Date._Year))
				Date._Day = NumOfDaysInMonth(Date._Month, Date._Year);
		}
		return Date;
	}
	void IncreaseDateByOneMonth() {
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate& Date, short Months) {
		for (int i = 1; i <= Months; i++) {
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonths(short Months) {
		*this = IncreaseDateByXMonths(*this, Months);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date) {
		Date._Year++;
		if (Date._Month == 2 && Date._Day > NumOfDaysInMonth(Date._Month, Date._Year)) {
			Date._Day = NumOfDaysInMonth(Date._Month, Date._Year);
		}
		return Date;
	}
	void IncreaseDateByOneYear() {
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, short Years) {
		Date._Year += Years;
		if (Date._Month == 2 && Date._Day > NumOfDaysInMonth(Date._Month, Date._Year)) {
			Date._Day = NumOfDaysInMonth(Date._Month, Date._Year);
		}
		return Date;

	}
	void IncreaseDateByXYears(short Years) {
		*this = IncreaseDateByXYears(*this, Years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date) {
		Date = IncreaseDateByXYears(Date, 10);
		return Date;
	}
	void IncreaseDateByOneDecade() {
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate& Date, int Decades) {
		Date = IncreaseDateByXYears(Date, 10 * Decades);
		return Date;
	}
	void IncreaseDateByXDecades(short Decades) {
		*this = IncreaseDateByXDecades(*this, Decades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date) {
		Date = IncreaseDateByXYears(Date, 100);
		return Date;
	}
	void IncreaseDateByOneCentury() {
		*this = IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date) {
		Date = IncreaseDateByXDecades(Date, 100);
		return Date;
	}
	void IncreaseDateByOneMillennium() {
		*this = IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOne(clsDate& Date) {
		if (Date._Day == 1) {
			if (Date._Month == 1) {
				Date._Month = 12;
				Date._Year--;
			}
			else { Date._Month--; }
			Date._Day = NumOfDaysInMonth(Date._Month, Date._Year);

		}
		else
			Date._Day--;
		return Date;
	}
	void DecreaseDateByOne() {
		*this = DecreaseDateByOne(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, short Days) {
		for (int i = 1; i <= Days; i++) {
			Date = DecreaseDateByOne(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(short Days) {
		*this = DecreaseDateByXDays(*this, Days);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date) {
		Date = DecreaseDateByXDays(Date, 7);
		return Date;
	}
	void DecreaseDateByOneWeek() {
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate& Date, short Weeks) {
		Date = DecreaseDateByXDays(Date, Weeks * 7);
		return Date;
	}
	void DecreaseDateByXWeeks(short Weeks) {
		*this = DecreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date) {
		Date._Month--;
		if (Date._Month == 0) {
			Date._Month = 12;
			Date._Year--;
		}
		if (Date._Day > NumOfDaysInMonth(Date._Month, Date._Year)) {
			Date._Day = NumOfDaysInMonth(Date._Month, Date._Year);
		}
		return Date;
	}
	void DecreaseDateByOneMonth() {
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& Date, short Months) {
		for (int i = 1; i <= Months; i++) {
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonths(short Months) {
		*this = DecreaseDateByXMonths(*this, Months);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date) {
		Date._Year--;
		if (Date._Day > NumOfDaysInMonth(Date._Month, Date._Year)) {
			Date._Day = NumOfDaysInMonth(Date._Month, Date._Year);
		}
		return Date;
	}
	void DecreaseDateByOneYear() {
		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, short Years) {
		Date._Year -= Years;
		if (Date._Day > NumOfDaysInMonth(Date._Month, Date._Year)) {
			Date._Day = NumOfDaysInMonth(Date._Month, Date._Year);
		}
		return Date;
	}
	void DecreaseDateByXYears(short Years) {
		*this = DecreaseDateByXYears(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date) {
		Date = DecreaseDateByXYears(Date, 10);
		return Date;
	}
	void DecreaseDateByOneDecade() {
		*this = DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, int Decades) {
		Date = DecreaseDateByXYears(Date, 10 * Decades);
		return Date;
	}
	void DecreaseDateByXDecades(short Decades) {
		*this = DecreaseDateByXDecades(*this, Decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date) {
		Date = DecreaseDateByXDecades(Date, 10);
		return Date;
	}
	void DecreaseDateByOneCentury() {
		*this = DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date) {
		Date = DecreaseDateByXDecades(Date, 100);
		return Date;
	}
	void DecreaseDateByOneMillennium() {
		*this = DecreaseDateByOneMillennium(*this);
	}

	static short DayOrder(clsDate Date) {
		double a = floor((14 - Date._Month) / 12);
		Date._Year -= a;
		Date._Month = Date._Month + (12 * a) - 2;
		Date._Day = Date._Day + Date._Year + floor(Date._Year / 4) - floor(Date._Year / 100) + floor(Date._Year / 400) + floor((31 * Date._Month) / 12);
		Date._Day = Date._Day % 7;
		return Date._Day;
	}
	short DayOrder() {
		return DayOrder(*this);
	}

	static bool IsEndOfWeek(clsDate& Date) {
		short dayorder = DayOrder(Date);
		return (dayorder == 6) ? true : false;
	}
	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate& Date) {
		short dayorder = DayOrder(Date);
		return (dayorder == 5 || dayorder == 6) ? true : false;
	}
	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate& Date) {
		short dayorder = DayOrder(Date);
		return (dayorder == 5 || dayorder == 6) ? 0 : 1;
	}
	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static short DaysUntilEndOfWeek(clsDate& Date) {
		return 6 - DayOrder(Date);
	}
	short DaysUntilEndOfWeek() {
		return DaysUntilEndOfWeek(*this);
	}

	static short DaysUntilEndOfMonth(clsDate& Date) {
		return NumOfDaysInMonth(Date._Month, Date._Year) - Date._Day;
	}
	short DaysUntilEndOfMonth() {
		return DaysUntilEndOfMonth(*this);
	}

	static short DaysUntilEndOfYear(clsDate& Date) {
		return NumOfDaysInYear(Date._Year) - CalculateDays(Date._Day, Date._Month, Date._Year);
	}
	short DaysUntilEndOfYear() {
		return DaysUntilEndOfYear(*this);
	}

	static int DeferenceBetweenTwoDates(clsDate Date1, clsDate Date2, bool EndDay = false) {

		if (!IsDate1EqualDate2(Date1, Date2)) {
			bool flag = true;
			if (!IsDate1LessThanDate2(Date1, Date2)) {
				clsDate temp = Date1;
				Date1 = Date2;
				Date2 = temp;
				flag = false;
			}
			if (Date1._Year == Date2._Year) {

				int d1days = CalculateDays(Date1._Day, Date1._Month, Date1._Year);
				int d2days = CalculateDays(Date2._Day, Date2._Month, Date2._Year);
				if (EndDay) {
					if (flag)
						return d2days - d1days + 1;
					else
						return(d2days - d1days + 1) * -1;
				}
				else
					if (flag)
						return d2days - d1days;
					else
						return(d2days - d1days) * -1;

			}
			else {
				int sum = 0;
				for (int i = Date1._Year + 1; i < Date2._Year; i++) {
					(IsLeapYear(i)) ? sum += 366 : sum += 365;
				}
				sum += CalculateDays(Date2._Day, Date2._Month, Date2._Year);
				sum += (NumOfDaysInYear(Date1._Year) - CalculateDays(Date1._Day, Date1._Month, Date1._Year));
				if (EndDay)
					if (flag)
						return sum + 1;
					else
						return(sum + 1) * -1;
				else
					if (flag)
						return sum;
					else
						return sum * -1;

			}

		}
		else if (IsDate1EqualDate2(Date1, Date2)) {
			return 0;
		}
		else
			return -1;
	}
	int DeferenceBetweenTwoDates(clsDate& Date, bool EndDay = false) {
		return  DeferenceBetweenTwoDates(*this, Date, EndDay);
	}

	static clsDate GetSystemDate()
	{
		clsDate Date;
		time_t t = time(0);
		tm* now = localtime(&t);
		Date._Year = now->tm_year + 1900;
		Date._Month = now->tm_mon + 1;
		Date._Day = now->tm_mday;
		return Date;
	}

	static int AgeInDays(clsDate& Date) {
		clsDate currentDate = GetSystemDate();
		int age = DeferenceBetweenTwoDates(Date, currentDate);
		return age;
	}
	int AgeInDays() {
		return AgeInDays(*this);
	}

	static int ActualVacationsDays(clsDate& Date1, clsDate& Date2) {
		int days = DeferenceBetweenTwoDates(Date1, Date2);
		int vacationDays = 0;
		if (days > 0) {
			for (int i = 1; i <= days; i++) {
				if (!IsWeekEnd(Date1)) {
					vacationDays++;
				}
				Date1 = IncreaseDateByOne(Date1);
			}
		}
		return vacationDays;
	}
	int ActualVacationsDays(clsDate Date) {
		return ActualVacationsDays(*this, Date);
	}

	static clsDate ReturnDateAfterVacationDays(clsDate& Date, int Days) {
		for (int i = 0; i <= Days; i++) {
			Date = IncreaseDateByOne(Date);
			if (IsWeekEnd(Date)) {
				--i;
			}
		}
		return Date;
	}
	clsDate ReturnDateAfterVacationDays(int Days) {
		return ReturnDateAfterVacationDays(*this, Days);
	}


	void Print() {
		cout << _Day << "/" << _Month << "/" << _Year << endl;;
	}

	static void printDateWithDayName(clsDate Date) {
		string days[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		int dayorder = DayOrder(Date);
		string currentday = days[dayorder];
		cout << currentday << " , ";
		cout << Date._Day << "/" << Date._Month << "/" << Date._Year << endl << endl;;
	}
	void printDateWithDayName() {
		printDateWithDayName(*this);
	}
	static void Calender(clsDate& Date) {
		string months[12] = { "Jan","Feb","March","April","May","June","July","Augest","Sep","Oct","Nov","Dec" };

		printf("\n   __________________%s__________________\n\n",
			months[Date._Month - 1].c_str());
		printf("   Sun   Mon   Tue   Wed   Thu   Fri   Sat\n");

		int numofdays = NumOfDaysInMonth(Date._Month, Date._Year);
		clsDate Temp = Date;
		Temp.Day = 1;
		int dayord = DayOrder(Temp);

		int i;
		for (i = 0; i < dayord; i++) {
			printf("     ");
		}

		for (int j = 1; j <= numofdays; j++) {
			printf("%6d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n   ________________________________________\n\n");

	}

	static string GetSystemDateTimeString() {

		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minutes, Seconds;
		Day = now->tm_mday;
		Month = now->tm_mon+1;
		Year = now->tm_year + 1900;
		Hour = now->tm_hour;
		Minutes = now->tm_min;
		Seconds = now->tm_sec;

		string Date = to_string(Day) + '/' + to_string(Month) + '/' + to_string(Year)
			+ " - " + to_string(Hour) + ':' + to_string(Minutes) + ':' + to_string(Seconds);
		return Date;

	}

	//------------------------------Constructors---------------------------------//
	clsDate() {
		time_t t = time(0);
		tm* now = localtime(&t);
		_Year = now->tm_year + 1900;
	    _Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}
	clsDate(string Date) {
		ConvertStringDatetoObjectDate(Date);
	}
	clsDate(short Day, short Month, short Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(int Days, int Year) {
		string Date = GetDateFromNumOfDays(Days, Year);
		ConvertStringDatetoObjectDate(Date);
	}
	//------------------------------End Of Constructors---------------------------------//




};

