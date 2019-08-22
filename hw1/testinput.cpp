#include<iostream>
#include<iomanip>
using namespace std;
bool inputYrMn(int& year, int& month);
int main()
{
    int year,month;
    char ans;
    do
    {
        cout << "Enter the year and month : ";
        cin >> year >> month;
        if(inputYrMn(year,month))
            cout << "your input are valid.\n";
        else
            cout << "your input are invalid, please try again.\n";

        cout << "Test again?(y/n)\n";
        cin >> ans;
        cout << "\n";
    }
    while(ans == 'y' || ans == 'Y');
    return 0;
}

bool inputYrMn(int& year, int& month)
{
    if(year < 1901 || year > 2099 || month < 1 || month > 12)
        return false;
    else
        return true;
}
