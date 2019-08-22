/*

Student ID:404410089
Name:Liao yi_ping
Dept:Computer Science and Information Engineering
Year:2

*/
#include <iostream>
#include <cstdlib>
using namespace std;
/*
class Rational which includes:
2 private members : numerator, denominator
3 constructors : default(0,1),
                user inputs 2 arguments,
                user inputs 1 argument to argument/1
2 accessor functions : getNumerator() and getDenominator()
Overload the input and output operators >> and << as friend functions
3 friend functions : *, /, ==
5 member functions : <, <=, >, >=, []
1 function to normalize the values
*/
class Rational
{
public:
    Rational();
    Rational(int);
    Rational(int,int);
    int getNumerator() const;
    int getDenominator() const;
    friend istream& operator >>(istream&, Rational&);
    friend ostream& operator <<(ostream&, const Rational&);
    friend Rational operator *(const Rational&, const Rational&);
    friend Rational operator /(const Rational&, const Rational&);
    friend bool operator ==(const Rational&, const Rational&);
    bool operator <(const Rational&) const;
    bool operator <=(const Rational&) const;
    bool operator >(const Rational&) const;
    bool operator >=(const Rational&) const;
    int& operator [](int index);
    void normalize();
private:
    int numerator;
    int denominator;
};
//default constructor (0,1)
Rational::Rational():numerator(0),denominator(1)
{
}
//user inputs 1 argument to argument/1
Rational::Rational(int wholeNumber):numerator(wholeNumber),denominator(1)
{
}
//user inputs 2 arguments to (numerator/denominator)
Rational::Rational(int first,int second)
{
    if(second==0)
    {
        cout << "Denominator can not be zero!!" <<"\n";
        exit(1);
    }
    if((first>0 && second<0) || (first<0 && second<0))
    {
        first = -first;
        second = -second;
    }
    numerator=first;
    denominator=second;
}
//accessor function to get numerator
int Rational::getNumerator() const
{
    return numerator;
}
//accessor function to get denominator
int Rational::getDenominator() const
{
    return denominator;
}
//overload the input operators >> as friend function
istream& operator >>(istream& input, Rational& number)
{
    int numerator,denominator;
    char slash;
    input >> numerator >> slash >> denominator;
    if(denominator == 0)
    {
        cout << "Denominator can not be zero." << "\n";
        exit(1);
    }
    if((numerator>0 && denominator<0) || (numerator<0 && denominator<0))
    {
        numerator = -numerator;
        denominator = -denominator;
    }
    number.numerator=numerator;
    number.denominator=denominator;
    return input;
}
//overload the output operators << as friend functions
ostream& operator <<(ostream& output, const Rational& number)
{
    output << number.numerator << "/" << number.denominator;
    return output;
}
//non-member overloading function about "plus"(first+second), and then return
Rational operator +(const Rational& first, const Rational& second)
{
    int numerator,denominator;
    numerator=first.getNumerator() * second.getDenominator() + first.getDenominator() * second.getNumerator();
    denominator=first.getDenominator() * second.getDenominator();
    return Rational(numerator,denominator);
}
//non-member overloading function about "minus"(first-second), and then return
Rational operator -(const Rational& first, const Rational& second)
{
    int numerator,denominator;
    numerator=first.getNumerator() * second.getDenominator() - first.getDenominator() * second.getNumerator();
    denominator=first.getDenominator() * second.getDenominator();
    return Rational(numerator,denominator);
}
//non-member overloading function about "negative"(-first), and then return
Rational operator -(const Rational& first)
{
    int numerator,denominator;
    numerator=first.getNumerator();
    denominator=first.getDenominator();
    return Rational(-numerator,denominator);
}
//overloading friend function about "multiple"(first*second), and then return
Rational operator *(const Rational& first, const Rational& second)
{
    int numerator,denominator;
    numerator=first.numerator * second.numerator;
    denominator=first.denominator * second.denominator;
    return Rational(numerator,denominator);
}
//overloading friend function about "divide"(first/second), and then return
Rational operator /(const Rational& first, const Rational& second)
{
    int numerator,denominator;
    numerator=first.numerator * second.denominator;
    denominator=first.denominator * second.numerator;
    return Rational(numerator,denominator);
}
//overloading friend function about "even"(first==second),return true if yes,else return false
bool operator ==(const Rational& first, const Rational& second)
{
    return(first.numerator * second.denominator == first.denominator * second.denominator);
}
//overloading member function about "smaller"(first<second),return true if yes,else return false
bool Rational::operator <(const Rational& first) const
{
    return(numerator * first.getDenominator() < first.getNumerator() * denominator);
}
//overloading member function about "smaller and equal"(first<=second),return true if yes,else return false
bool Rational::operator <=(const Rational& first) const
{
    return(numerator * first.getDenominator() <= first.getNumerator() * denominator);
}
//overloading member function about "greater"(first>second),return true if yes,else return false
bool Rational::operator >(const Rational& first) const
{
    return(numerator * first.getDenominator() > first.getNumerator() * denominator);
}
//overloading member function about "greater and equal"(first>=second),return true if yes,else return false
bool Rational::operator >=(const Rational& first) const
{
    return(numerator * first.getDenominator() >= first.getNumerator() * denominator);
}
//overloading member function about [0]: numerator; [1]: denominator
int& Rational::operator [](int index)
{
    if(index == 0)
        return numerator;
    else if(index == 1)
        return denominator;
    else
    {
        cout << "Input error." << "\n";
        exit(1);
    }
}
//find gcd of numerator and denominator,and use it to divide each of them
void Rational::normalize()
{
    int a = abs(numerator);
    int b = abs(denominator);
    int temp;
    while(1)
    {
        temp=b;
        b=a%b;
        a=temp;
        if(b==0) break;
    }
    int gcd = temp;
    numerator/=gcd;
    denominator/=gcd;
}

int main()
{
    Rational de;
    Rational single(90);
    Rational first;
    Rational second;
    Rational display;
    //show the default rational
    cout << "Default : rational = " << de << "\n";
    //show the single parameter rational (numerator/1)
    cout << "Single parameter : rational = " << single << "\n";
    //let user input 2 rational
    cout << "Input format example : 4/8 (slash(/) must be entered ! )" << "\n";
    cout << "Input first(numerator/denominator):";
    cin >> first;
    cout << "Input second(numerator/denominator):";
    cin >> second;
    //simplify 2 rational
    first.normalize();
    second.normalize();
    //show 2 rational after simplify
    cout << "first: " << first << "\n";
    cout << "second: " << second << "\n";
    //add 2 rational,and then show it
    display = first + second;
    display.normalize();
    cout << "first + second: " << display << "\n";
    //subtract 2 rational,and then show it
    display = first - second;
    display.normalize();
    cout << "first - second: " << display << "\n";
    //multiple 2 rational,and then show it
    display = first * second;
    display.normalize();
    cout << "first * second: " << display << "\n";
    //divide 2 rational,and then show it
    display = first / second;
    display.normalize();
    cout << "first / second: " << display << "\n";

    cout << "-first: " << -first << "\n";
    cout << "-second: " << -second << "\n";
    cout << "first < second: " << ((first<second) ? "Yes" : "No") << "\n";
    cout << "first <= second: " << ((first<=second) ? "Yes" : "No") << "\n";
    cout << "first > second: " << ((first>second) ? "Yes" : "No") << "\n";
    cout << "first >= second: " << ((first>=second) ? "Yes" : "No") << "\n";

    //use [] to refresh first's value and multiple it by 100
    cout << "Refresh first'variable and multiple 100 by []:";
    int refresh1,refresh2;
    char slash;
    cin >> refresh1 >> slash >> refresh2;
    //use [] and multiple it by 100
    first[0] = refresh1*100;
    first[1] = refresh2*100;
    cout << "After refresh: " << first << "\n";

    return 0;
}
