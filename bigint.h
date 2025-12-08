#include <cstdint>
#include <iomanip>
#include "define.h"
using namespace std;
std::ostream&
operator<<( std::ostream& dest, __int128_t value ) /// https://stackoverflow.com/questions/25114597/how-to-print-int128-in-g
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}
string NotCaseSensitive(string s)
{
    int string_length=s.length();                  /// Numarul de caractere al comenzii citite de la tastatura | The string length command of the keyboard input
    for(int i=0;i<string_length;i++)               /// Transformam orice litera mare din comanda in litera mica pentru ca comanda sa nu fie case sensitive
        if(s[i]>='A' && s[i]<='Z')                 /// We convert any uppercase letter in the command to lowercase so that the command to be not case sensitive
            s[i]+=32;
    return s;
}
string conversion(string a)
{
    a = NotCaseSensitive(a);
    if(a=="pi")
        a=pi;
    else if(a=="e")
        a=e;
    else if(a=="a" || a=="ans" || a=="answer" || a=="rez" || a=="rezultat")
        a=Answer;
    return a;
}
__int128 StringToInt(string s)
{
    s=conversion(s);
    if(s=="inf"||s=="cinf")
        return INT128_MAX;
    else if(s=="-inf")
        return INT128_MIN;

    __int128 nr = 0, p = 1;
    int n = s.size();
    for(int i = n-1; i>=0; i--)
    {
        if(s[i] == '-' && i == 0)
            nr = -nr;
        else if(s[i]>='0' && s[i]<='9')
        {
            nr += p * (s[i] - 48);
            p *= 10;
        }
        else
        {
            nr = 0;
            p = 1;
        }
    }
    return nr;
}
__int128 CinIntNumber()
{
    __int128 n;
    string a;
    cin>>a;
    n = StringToInt(a);
    return n;
}
struct ScientificForm                              /// Structura reprezinta forma stiintifica a unui numar real (x*10^y), cu coeficientul si exponentul numere intregi de tip __int128
{                                                  /// This structure returns scientific form of a real number  (x*10^y), with coefficient and exponent which are __int128 integers
    __int128 coefficient, exponent;
};
struct Fraction
{
    __int128 numerator, denominator;
};
ScientificForm float_to_int(long double f)         /// Returneaza forma stiintifica a unui numar real            | Return scientific form of a real number
{
    ScientificForm n;
    n.exponent=0;
    while(f!=(__int128)f                           /// Ca sa extragem zecimalele din numarul real intr-un intreg | To extract decimals from real number to a integer
          && f*10<=INT128_MAX && f*10>=INT128_MIN) /// Ca sa nu dea underflow sau overflow                       | To not get overflow or underflow
    {
        f*=10;
        n.exponent--;
    }
    if(f==1/0.0||f==-1/0.0)
    {
        n.exponent=INT128_MAX-1;
        n.coefficient=1;
    }
    else if(f!=f)
    {
        n.exponent=INT128_MAX;
        n.coefficient=0;
    }
    else
    {
        while(f>INT128_MAX||f<INT128_MIN)
        {
            f /= 10;
            if(n.exponent != INT128_MAX)
                n.exponent++;
        }
        n.coefficient=f;
    }
    while(n.coefficient%10==0 && n.coefficient!=0) /// Daca numarul n e de forma 100*10^2, structura repetitiva va incerca sa faca sa fie de forma 1*10^4
    {                                              /// If n number is like 100*10^2, the repetitive structure tries to be like 1*10^4
        if(n.exponent != INT128_MAX)
            n.exponent++;
        n.coefficient /= 10;
    }
    return n;
}
void show_floated_int(ScientificForm n)            /// Afiseaza forma stiinfica a numarului real      | Shows scientific form of real number
{
    __int128 p=1,x,ct=0;
    if(n.exponent==INT128_MAX)                     /// In loc de x*10^y este x impartit la 0          | Instead of x*10^y is x over 0
    {
        if(n.coefficient==0)
            cout<<0/0.0;
        else
            cout<<"cinf";
    }
    else if(n.exponent==INT128_MAX-1)              /// In loc de x*10^y este x inmultit cu infinit    | Instead of x*10^y is x times infinity
    {
        if(n.coefficient==0)
            cout<<0;
        else
            cout<<n.coefficient/0.0;
    }
    else if(n.exponent==INT128_MIN)                /// In loc de x*10^y este x impartit la infinit    | Instead of x*10^y is x over infinity
    {
        if(n.coefficient==0)
            cout<<0;
        else if(n.coefficient<0)
            cout<<"-0.0";
        else if(n.coefficient>0)
            cout<<"0.0";
    }
    else if(n.exponent<0)
    {
        if(n.coefficient<0)
            cout<<'-';
        for(__int128 i=-1; i>=n.exponent; i--)
            p=p*10;
        if(n.coefficient<0)
            cout<<-n.coefficient/p<<'.';
        else
            cout<<n.coefficient/p<<'.';
        x=n.coefficient%p;
        while(x!=0)
        {
            x=x/10;
            ct--;
        }
        for(__int128 i=n.exponent;i<ct;i++)
            cout<<0;
        if(n.coefficient<0)
            cout<<-n.coefficient%p;
        else
            cout<<n.coefficient%p;
    }
    else if(n.exponent>=0)
    {
        cout<<n.coefficient;
        for(__int128 i=1; i<=n.exponent; i++)
            cout<<0;
    }
    cout<<" = "<<n.coefficient;
    if(n.exponent==INT128_MAX)
        cout<<" * cinf"<<endl;
    else if(n.exponent==INT128_MAX-1)
        cout<<" * 10 ^ "<< 1/0.0<<endl;
    else if(n.exponent==INT128_MIN)
        cout<<" * 10 ^ "<<-1/0.0<<endl;
    else
        cout<<" * 10 ^ "<<n.exponent<<endl;
}
bool FactorialInitialization = 0;                  /// Aceasta variabila retine daca valorile factorialelor au fost atribuite (1) sau nu (0)
                                                   /// This variable stores if the factorial values were assigned (1) or not (0)

int MaxNumberFact = 33;                            /// Cel mai mare numar caruia pot sa ii calculez factorialul (33) | The biggest number that I can calculate its factorial (33)

__int128 FactorialVector[33 + 1];                  /// Vectorul care stocheaza factorialul fiecarui numar natural mai mic sau egal cu MaxNumberFact (de la 0 la MaxNumberFact sunt MaxNumberFact + 1 elemente)
                                                   /// The vector which store factorial of each natural number between 0 and MaxNumberFact (in total are MaxNumberFact + 1 elements)

ScientificForm factorial(int n)                    /// Functia care returneaza factorialul unui numar si umple cu valori vectorului FactorialVector pe baza factorialului fiecarui numar
{                                                  /// The function which returns factorial of a number and put values on FactorialVector based on factorial of each number
    if(FactorialInitialization == 0)
    {
        __int128 p=1;                              /// p este factorialul indicelui i curent | p is the factorial for current index (i)
        FactorialVector[0]=1;
        for(int i=1;i<=MaxNumberFact;i++)
        {
            p=p*i;
            FactorialVector[i]=p;
        }
        FactorialInitialization = 1;
    }
    ScientificForm nr;
    if(n>=0 && n<=MaxNumberFact)
    {
        nr.coefficient = FactorialVector[n];        /// https://zeptomath.com/calculators/factorial.php
        nr.exponent = 0;
    }
    else if(n>MaxNumberFact)
    {
        long double x = FactorialVector[33];
        if(n > 1755)
            n = 1755;
        for(int i=34;i<=n;i++)
            x*=i;
        cout<<"Precizie pierduta la calcularea factorialului | Precision lost at calculating this factorial"<<endl;
        nr=float_to_int(x);
    }
    else
    {
        nr.coefficient = 1;                        /// Returneaza infinitul complex (cinf = 1/0) in cazul factorialului unui numar negativ
        nr.exponent = INT128_MAX;                  /// Returns complex infinity (cinf = 1/0) if we want to return a factorial of a negative number
    }
    return nr;
}
long double div_to_float(Fraction fr)
{
    long double nr;
    if(fr.numerator == INT128_MAX)
        nr = (1/0.0)/fr.denominator;
    else if(fr.numerator == INT128_MIN)
        nr = (-1/0.0)/fr.denominator;
    else if(fr.denominator == INT128_MAX)
        nr = fr.numerator/(1/0.0);
    else if(fr.denominator == INT128_MIN)
        nr = fr.numerator/(-1/0.0);
    else
    {
        if(fr.numerator == 0 && fr.denominator != 0)
        {
            if(language == 0)
                cout<<"Precision loss! 0 converted to 0.0 \n";
            else
                cout<<"Precizie pierduta! 0 convertit la 0.0 \n";
        }
        else if(fr.denominator == 0 && fr.numerator != 0)
        {
            if(language == 0)
                cout<<"Precision loss! cinf converted to inf \n";
            else
                cout<<"Precizie pierduta! cinf convertit la inf \n";
        }
        nr = (long double)fr.numerator/fr.denominator;
    }
    return nr;
}
ScientificForm div_int(Fraction fr)                /// In aceasta functie vrem sa returnam forma stiintifica a rezultatului real al lui x/y | This function returns scientific form of real result x/y
{
    long double nr;
    ScientificForm n;
    if(fr.numerator != 0 && fr.denominator == 0)
    {
        n.coefficient = 1;
        n.exponent = INT128_MAX;
        return n;
    }
    nr = div_to_float(fr);
    n  = float_to_int(nr);
    return n;
}
Fraction int_div(ScientificForm n)
{
    Fraction f;
    f.numerator = n.coefficient;
    f.denominator = 1;
    if(n.exponent == INT128_MAX)
    {
        f.denominator=0;
        if(n.coefficient == 0)
            f.numerator = 0;
        else if(n.coefficient != 0)
            f.numerator = 1;
        return f;
    }
    else if(n.coefficient == 0)
    {
        f.numerator = 0;
        f.denominator = 1;
        return f;
    }
    else if(n.exponent == INT128_MAX - 1)
    {
        f.numerator   = INT128_MAX;
        f.denominator = sgn(n.coefficient);
        return f;
    }
    else if(n.exponent == INT128_MIN)
    {
        f.denominator = INT128_MAX;
        f.numerator   = sgn(n.coefficient);
        return f;
    }
    while(n.exponent<0)
    {
        if(f.denominator <= (INT128_MAX - 1) / 10 && f.denominator >= (INT128_MIN + 1) / 10)
            f.denominator  *= 10;
        else if(f.numerator / 10 != 0)
            f.numerator    /= 10;
        else
        {
            f.denominator = INT128_MAX;
            f.numerator   = sgn(n.coefficient);
            return f;
        }
        n.exponent+=1;
    }
    while(n.exponent>0)
    {
        if(f.numerator <= (INT128_MAX - 1) / 10 && f.numerator >= (INT128_MIN + 1) / 10)
            f.numerator*=10;
        else if(f.denominator / 10 != 0)
            f.denominator/=10;
        else
        {
            f.numerator   = INT128_MAX;
            f.denominator = sgn(n.coefficient);
            return f;
        }
        n.exponent-=1;
    }
    return f;
}
ScientificForm CinScientificForm()
{
    ScientificForm f;
    f.coefficient = CinIntNumber();
    f.exponent    = CinIntNumber();
    while(f.coefficient%10==0 && f.coefficient!=0) /// Daca numarul n e de forma 100*10^2, structura repetitiva va incerca sa faca sa fie de forma 1*10^4
    {                                              /// If n number is like 100*10^2, the repetitive structure tries to be like 1*10^4
        if(f.exponent < INT128_MAX-1 && f.exponent > INT128_MIN)
            f.exponent++;
        f.coefficient/=10;
    }
    return f;
}
__int128 GCD (__int128 a, __int128 b)              /// https://www.pbinfo.ro/articole/73/cmmdc-si-cmmmc-algoritmul-lui-euclid
{
    if(a==0 || b==0)
    {
        __int128 maxim = max(a,b);
        maxim = max(maxim,(__int128)1);
        return maxim;
    }
    __int128 r;
    while(b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}
Fraction simplification(Fraction n)
{
    bool ok = 0;
    if(n.numerator * n.denominator == 0)
    {
        if(n.numerator != 0)
            n.numerator = 1;
        else if(n.denominator != 0)
            n.denominator = 1;
        return n;
    }
    else if(n.numerator == INT128_MAX || n.numerator == INT128_MIN || n.denominator == INT128_MAX || n.denominator == INT128_MIN)
    {
        if(n.numerator == n.denominator)
        {
            n.numerator = 1;
            n.denominator = 1;
        }
        else if(n.numerator == -n.denominator)
        {
            n.numerator = -1;
            n.denominator = 1;
        }
        else if(n.numerator == INT128_MAX)
            n.denominator = sgn(n.denominator);
        else if(n.numerator == INT128_MIN)
        {
            n.denominator = -sgn(n.denominator);
            n.numerator   = INT128_MAX;
        }
        else if(n.denominator == INT128_MAX)
            n.numerator = sgn(n.numerator);
        else if(n.denominator == INT128_MIN)
        {
            n.numerator   = -sgn(n.numerator);
            n.denominator = INT128_MAX;
        }
        return n;
    }
    else if(n.numerator > 0 && n.denominator > 0)
    {
        n.numerator   = -n.numerator;
        n.denominator = -n.denominator;
    }
    else if(n.numerator > 0)
    {
        ok = 1;
        n.numerator = -n.numerator;
    }
    else if(n.denominator > 0)
    {
        ok = 1;
        n.denominator = -n.denominator;
    }
    __int128 gcd = GCD(n.numerator,n.denominator);
    n.numerator   /= gcd;
    n.denominator /= gcd;
    if(n.numerator != (INT128_MIN+1) && ok == 1)
    {
        n.numerator = -n.numerator;
        ok = 0;
    }
    else if(n.denominator != (INT128_MIN+1) && ok == 1)
    {
        n.denominator = -n.denominator;
        ok = 0;
    }
    return n;
}
void CoutFraction(Fraction f)
{
    if(f.denominator == INT128_MIN)
        cout<<f.numerator<<" / -inf";
    else if(f.denominator == INT128_MAX)
        cout<<f.numerator<<" / inf";
    else if(f.numerator == INT128_MIN)
        cout<<"-inf / "<<f.denominator;
    else if(f.numerator == INT128_MAX)
        cout<<"inf / "<<f.denominator;
    else
        cout<<f.numerator<<" / "<<f.denominator;
}
Fraction CinFraction()
{
    Fraction n;
    n.numerator   = CinIntNumber();
    n.denominator = CinIntNumber();
    n = simplification(n);
    if(debug == 1)
    {
        if(language == 0)
            cout<<"The fraction from the input is: ";
        else
            cout<<"Fractia citita este: ";
        CoutFraction(n);
        cout<<endl;
    }
    return n;
}
void SameDenominator(Fraction &a, Fraction &b)
{
    if( a.denominator != 0 && b.denominator != 0
       && !(a.numerator == INT128_MAX || a.numerator == INT128_MIN || a.denominator == INT128_MAX || a.denominator == INT128_MIN)
       && !(b.numerator == INT128_MAX || b.numerator == INT128_MIN || b.denominator == INT128_MAX || b.denominator == INT128_MIN) )
    {
        __int128 gcd = GCD(a.denominator,b.denominator);
        __int128 factor1 = a.denominator/gcd;
        __int128 factor2 = b.denominator/gcd;
        a.numerator   *= factor2;
        a.denominator *= factor2;
        b.numerator   *= factor1;
        b.denominator *= factor1;
    }
}
