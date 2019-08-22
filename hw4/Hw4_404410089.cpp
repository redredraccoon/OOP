/*

Student ID:404410089
Name:Liao yi_ping
Dept:Computer Science and Information Engineering
Year:2

*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
/*
class:
Construct: by BigInt, char array, int, default.
Destruct: releases all memory that has been allocated.
Overload: copy constructor, +, -, <<.
Private member variable: number=>pointer to int array.
                         digit=>used size of array.
                         sign=> positive or negative of BigInt.
*/
class BigInt
{
public:
    BigInt& operator =(const BigInt &a);
    BigInt(const BigInt &a);
    BigInt(const char *a);
    BigInt(const int a);
    BigInt();
    ~BigInt();
    friend int cmp(const BigInt &a, const BigInt &b);
    friend BigInt operator +(BigInt a, BigInt b);
    friend BigInt operator -(BigInt a, BigInt b);
    friend ostream& operator <<(ostream& output, const BigInt &a);

private:
    int *number;
    int digit;
    int sign;
};
/*
compare 2 BigInt for bigger and smaller
a>b=>1
a<b=>2
a=b=>3
*/
int cmp(const BigInt &a, const BigInt &b)
{
    int len = (a.digit > b.digit) ? a.digit : b.digit;
    if(a.digit > b.digit)   return 1;
    else if(a.digit < b.digit)  return 2;
    for(int i=0; i<a.digit; i++)
    {
        if(a.number[i] > b.number[i])   return 1;
        if(a.number[i] < b.number[i])   return 2;
    }
    if(a.sign == b.sign)    return 3;
    return 0;
}
/*
copy constructor
use "*this" to use class member
*/
BigInt& BigInt::operator =(const BigInt &a)
{

    if(cmp(*this,a) == 3)   return *this;

    delete [] number;

    number = new int [a.digit];
    digit = a.digit;
    sign = a.sign;
    for(int i=0; i<a.digit; i++)    number[i] = a.number[i];
    return *this;
}
/*
default zero
*/
BigInt::BigInt()
{
    digit = 1;
    number = new int [1];
    number[0] = 0;
    sign = 0;
}
/*
destruct: releases all memory that has been allocated.
*/
BigInt::~BigInt()
{
    delete [] number;
}
/*
if it is char array
*/
BigInt::BigInt(const char *a)
{
    if(a[0] == '-') sign = 1;
    else if(a[0] == '+' || (a[0]>='0' && a[0]<='9'))    sign = 0;

    int now(-1);
    int len = strlen(a);

    for(int i=0; i<len; i++)//find the position which the number start
    {
        if(a[i]=='+' || a[i]=='-' || a[i]=='0') continue;
        else
        {
            now = i;
            break;
        }
    }

    if(now == -1)   now = len-1;

    number = new int [len*2];

    digit = len-now;//just number used.

    int record(0);
    for(int i=now; i<len; i++)number[record++] = a[i]-'0';//transfer to
}
/*
if it is int
*/
BigInt::BigInt(int a)
{
    sign = (a < 0) ? 1 : 0;//check sign.

    a = abs(a);//absolute value

    int len(1);
    int tempNum(a);//Count number's digits.
    while ((tempNum/10) > 0)
    {
        len++;
        tempNum /= 10;
    }
    len++;

    number = new int [len*2];
    digit = len;

    for(int i=0; i<len; i++)
    {
        number[i] = a%10;
        a/=10;
    }

    for(int i=0,j=digit-1; i<j; i++,j--)//reverse
    {
        int temp=number[j];
        number[j]=number[i];
        number[i]=temp;
    }
}
/*
if it is BigInt
*/
BigInt::BigInt(const BigInt &a)
{
    int len = a.digit;
    number = new int [len*2];
    digit = len;
    sign = a.sign;
    for(int i=0; i<len; i++)number[i] = a.number[i];
}
/*
output the BigInt
*/
ostream& operator <<(ostream& output, const BigInt &a)
{
    if(a.sign == 1) output << "-";
    for(int i=0; i<a.digit; i++)    output << a.number[i];
    return output;
}
/*
add 2 BigInt, and return the result
*/
BigInt operator +(BigInt a, BigInt b)
{
    if(cmp(a,b) == 2)//If b > a, swap it.
    {
        BigInt temp=b;
        b=a;
        a=temp;
    }

    int len = (a.digit > b.digit) ? a.digit : b.digit;//get max of used digit number

    int manu_a[len];
    memset(manu_a,0,sizeof(manu_a));
    int manu_b[len];
    memset(manu_b,0,sizeof(manu_b));

    for(int i=0,j=a.digit-1; i<j; i++,j--)//reverse
    {
        int temp=a.number[j];
        a.number[j]=a.number[i];
        a.number[i]=temp;
    }
    for(int i=0,j=b.digit-1; i<j; i++,j--)//reverse
    {
        int temp=b.number[j];
        b.number[j]=b.number[i];
        b.number[i]=temp;
    }

    for(int i=0; i<a.digit; i++) manu_a[i] = a.number[i];
    for(int i=0; i<b.digit; i++)manu_b[i] = b.number[i];

    int res(0);//decide result's sign is + or -
    int ss(0);//decide which matters to add

    if(a.sign == b.sign && a.sign == 1)//-a+-b
    {
        res = 1;
        ss = 0;
    }
    else if(a.sign == b.sign && a.sign == 0)//a+b
    {
        res = 0;
        ss = 0;
    }
    else//-a+b or a+-b
    {
        res = a.sign;
        ss = 1;
    }

    int result[len+10];
    memset(result,0,sizeof(result));

    for(int i=0; i<len; i++)
    {
        if(ss == 0)//add
        {
            result[i] = result[i] + manu_a[i] + manu_b[i];
            result[i+1] = result[i]/10;
            result[i]%=10;
        }
        else if(ss == 1)//minus
        {
            result[i] = result[i] + manu_a[i] - manu_b[i];
            if(result[i] < 0)
            {
                result[i+1]--;
                result[i]+=10;
            }
        }
    }

    int result_len(1);
    for(int i=0; i<len+10; i++)// find the last nonzero index.
    {
        if(result[i]!=0)    result_len = i+1;
    }

    for(int i=0,j=result_len-1; i < j; i++,j--)//reverse
    {
        int temp=result[j];
        result[j]=result[i];
        result[i]=temp;
    }

    char end_result[result_len+10];// result(int array) transfer to end_result(char array)
    memset(end_result,'\0',sizeof(end_result));

    if(res == 1)end_result[0] = '-';
    else end_result[0] = '+';
    for(int i=1; i<=result_len; i++)    end_result[i] = '0' + result[i-1];

    return BigInt(end_result);
}
/*
minus 2 BigInt
deal with sign, and then go to add
*/
BigInt operator -(BigInt a, BigInt b)
{
    b.sign=(b.sign==0) ? 1 : 0;
    return a + b;
}

int main()
{
    cout << "Test:" << "\n";
    BigInt a("314159265358979323846264338327950288419716939937510"), c(a);
    BigInt *b = new BigInt(1618033988);
    c = a + *b;
    cout << a << " + " << *b << " = " << c << "\n";
    c = a - *b;
    cout << a << " - " << *b << " = " << c << "\n";
    cout << "\n";

    cout << "Input 2 numbers --- the number should < 100000 digits." << "\n";
    char first[100000];
    char second[100000];
    memset(first,'\0',sizeof(first));
    memset(second,'\0',sizeof(second));
    while(cin >> first >> second)
    {
        BigInt f(first), s(second);
        cout << "first: " << f << "\n";
        cout << "second: " << s << "\n";
        cout << "first + second: " << f+s << "\n";
        cout << "first - second: " << f-s << "\n";

        memset(first,'\0',sizeof(first));
        memset(second,'\0',sizeof(second));
    }
    return 0;
}

