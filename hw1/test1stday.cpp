#include<iostream>
#include<iomanip>
using namespace std;
void get1stDayOfMonth(int year, int month, int& weekDay, int& numDays, int day[]);
int main()
{
    int year,month;
    int weekDay=1, numDays=1;
    int day[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    char ans;
    do
    {
        cout << "Enter the year and month : ";
        cin >> year >> month;
        get1stDayOfMonth(year, month, weekDay, numDays, day);
        cout << "weekDay is " << weekDay << ",   numDays is " << numDays <<"\n";
        cout << "Test again?(y/n)\n";
        cin >> ans;
        cout << "\n";
    }
    while(ans == 'y' || ans == 'Y');
    return 0;
}

void get1stDayOfMonth(int year, int month, int& weekDay, int& numDays, int day[])
{
    weekDay=(year-1+(year-1)/4-(year-1)/100+(year-1)/400)%7;

    if ((year%4 == 0 && year%100 != 0) || year%400 == 0)
    {
        if (month>=2)
        {
            day[1]=29;
        }
    }

    for (int i=0; i<(month-1); i++)
    {
        weekDay+=day[i];
    }
    numDays=(weekDay+1)%7;
}

