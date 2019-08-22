#include<iostream>
#include<iomanip>
using namespace std;

bool inputYrMn(int& year, int& month);
void get1stDayOfMonth(int year, int month, int& weekDay, int& numDays, int day[]);
void showCalendar(int year, int month, int& numDays,int day[]);

bool inputYrMn(int& year, int& month)
{
    if(year < 1901 || year > 2099 || month < 1 || month > 12)
        return false;
    else
        return true;
}
/*
Preconditions:year is the year just input, and the month is, too.
Postconditions:confirm year and month are logical.
*/
void get1stDayOfMonth(int year, int month, int& weekDay, int& numDays, int day[])
{
    weekDay=(year-1+(year-1)/4-(year-1)/100+(year-1)/400)%7;

    if ((year%4 == 0 && year%100 != 0) || year%400 == 0)
    {
        if (month>=2) //若該年是閏年則餘數+1,2月份也改為29天
        {
            day[1]=29;
        }
    }

    for (int i=0; i<(month-1); i++) //求出欲求該年份1月1日之總天數
    {
        weekDay+=day[i];
    }
    numDays=(weekDay+1)%7; //求出欲求該月份1日星期幾(因為從星期日計算故+1)
}
/*
Preconditions:year and month are the input items help we get the calendar.
              weekDay and numDays are reference parameters we will get from this function.
              Array day[] keep the number of days of each month.
Postconditions:check if the year is leap year, and get the weekDay about the number of days of the month.
               Get the numDays about which is the day of the week of the first day of the month.
*/
void showCalendar(int year, int month, int& numDays,int day[])
{
    cout << "-----------------------------\n";
    cout << "        " << year;
    switch(month)
    {
    case 1:
        cout << " January\n";break;
    case 2:
        cout << " February\n";break;
    case 3:
        cout << " March\n";break;
    case 4:
        cout << " April\n";break;
    case 5:
        cout << " May\n";break;
    case 6:
        cout << " June\n";break;
    case 7:
        cout << " July\n";break;
    case 8:
        cout << " August\n";break;
    case 9:
        cout << " September\n";break;
    case 10:
        cout << " October\n";break;
    case 11:
        cout << " November\n";break;
    case 12:
        cout << " December\n";break;
    }
    cout << "-----------------------------\n";
    cout << " SUN MON TUE WED THU FRI SAT\n";
    for (int i=0; i<numDays; i++)
    {
        cout << setw(4) << setfill(' ') << "";
    }
    int count = numDays%7; //該月份1日從星期幾開始依序填入日期
    for (int i=0; i<day[month-1]; i++)
    {
        cout << setw(4) << setfill(' ') << i+1; //2個字為一組,不足填入空格
        if (count>=6) //每週六後換行
        {
            cout << "\n";
            count=0;
        }
        else
        {
            count++;
        }
    }
    cout << "\n";
    cout << "-----------------------------\n";
}
/*
Preconditions:year and month are the input items.
              numDays is reference parameters keeps the day of the week of the first day of the month.
              Array day[] keep the number of days of each month.
Postconditions:print out the calendar.
*/

int main()
{
    while(1)
    {
        int year,month;
        cout << "Please enter year (from 1901 to 2099) : ";
        cin >> year;
        cout << "Please enter month (from 1 to 12) : ";
        cin >> month;
        if(inputYrMn(year,month))
        {
            int weekDay=1, numDays=1;
            int day[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
            get1stDayOfMonth(year, month, weekDay, numDays, day);
            showCalendar(year, month, numDays, day);
        }
        else
            cout << "Input error ! Please try again.\n";
    }
}
