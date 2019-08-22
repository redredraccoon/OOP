#include<iostream>
#include<iomanip>
using namespace std;
void showCalendar(int year, int month, int& numDays,int day[]);
int main()
{
    int year,month,numDays;
    int day[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    char ans;
    do
    {
        cout << "Enter the year and month and numDays: ";
        cin >> year >> month >> numDays;
        if ((year%4 == 0 && year%100 != 0) || year%400 == 0)
        {
            if (month>=2)
            {
                day[1]=29;
            }
        }
        showCalendar(year, month, numDays, day);
        cout << "Test again?(y/n)\n";
        cin >> ans;
        cout << "\n";
    }
    while(ans == 'y' || ans == 'Y');
    return 0;
}

void showCalendar(int year, int month, int& numDays,int day[])
{
    cout << "-----------------------------\n";
    cout << "        " << year;
    switch(month)
    {
    case 1:
        cout << " January\n";
        break;
    case 2:
        cout << " February\n";
        break;
    case 3:
        cout << " March\n";
        break;
    case 4:
        cout << " April\n";
        break;
    case 5:
        cout << " May\n";
        break;
    case 6:
        cout << " June\n";
        break;
    case 7:
        cout << " July\n";
        break;
    case 8:
        cout << " August\n";
        break;
    case 9:
        cout << " September\n";
        break;
    case 10:
        cout << " October\n";
        break;
    case 11:
        cout << " November\n";
        break;
    case 12:
        cout << " December\n";
        break;
    }
    cout << "-----------------------------\n";
    cout << " SUN MON TUE WED THU FRI SAT\n";
    for (int i=0; i<numDays; i++)
    {
        cout << setw(4) << setfill(' ') << "";
    }
    int count = numDays%7;
    for (int i=0; i<day[month-1]; i++)
    {
        cout << setw(4) << setfill(' ') << i+1;
        if (count>=6)
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


