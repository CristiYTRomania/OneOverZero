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
__int128 StringToInt(string s)
{
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
string NotCaseSensitive(string s)
{
    int nr_caractere=s.length();                  /// Numarul de caractere al comenzii citite de la tastatura | The string length command of the keyboard input
    for(int i=0;i<nr_caractere;i++)               /// Transformam orice litera mare din comanda in litera mica pentru ca comanda sa nu fie case sensitive
        if(s[i]>='A' && s[i]<='Z')                /// We convert any uppercase letter in the command to lowercase so that the command to be not case sensitive
            s[i]+=32;
    return s;
}
string convertire(string a)
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
__int128 CitireNrIntreg()
{
    __int128 n;
    string a;
    cin>>a;
    a = convertire(a);
    n = StringToInt(a);
    return n;
}
struct FormaStiintifica                            /// Structura reprezinta forma stiintifica a unui numar real (x*10^y), cu coeficientul si exponentul numere intregi de tip __int128
{                                                  /// This structure returns scientific form of a real number  (x*10^y), with coefficient and exponent which are __int128 integers
    __int128 coeficient, exponent;
};
struct Fractie
{
    __int128 numarator, numitor;
};
FormaStiintifica float_to_int(long double f)       /// Returneaza forma stiintifica a unui numar real | Return scientific form of a real number
{
    FormaStiintifica n;
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
        n.coeficient=1;
    }
    else if(f!=f)
    {
        n.exponent=INT128_MAX;
        n.coeficient=0;
    }
    else
    {
        while(f>INT128_MAX||f<INT128_MIN)
        {
            f/=10;
            n.exponent++;
        }
        n.coeficient=f;
    }
    while(n.coeficient%10==0 && n.coeficient!=0)   /// Daca numarul n e de forma 100*10^2, structura repetitiva va incerca sa faca sa fie de forma 1*10^4
    {                                              /// If n number is like 100*10^2, the repetitive structure tries to be like 1*10^4
        n.exponent++;
        n.coeficient/=10;
    }
    return n;
}
void show_floated_int(FormaStiintifica n)          /// Afiseaza forma stiinfica a numarului real      | Shows scientific form of real number
{
    __int128 p=1,x,ct=0;
    if(n.exponent==INT128_MAX)                     /// In loc de x*10^y este x impartit la 0          | Instead of x*10^y is x over 0
    {
        if(n.coeficient==0)
            cout<<0/0.0;
        else
            cout<<"cinf";
    }
    else if(n.exponent==INT128_MAX-1)              /// In loc de x*10^y este x inmultit cu infinit    | Instead of x*10^y is x times infinity
    {
        if(n.coeficient==0)
            cout<<0;
        else
            cout<<n.coeficient/0.0;
    }
    else if(n.exponent==INT128_MIN)                /// In loc de x*10^y este x impartit la infinit    | Instead of x*10^y is x over infinity
    {
        if(n.coeficient==0)
            cout<<0;
        else if(n.coeficient<0)
            cout<<"-0.0";
        else if(n.coeficient>0)
            cout<<"0.0";
    }
    else if(n.exponent<0)
    {
        if(n.coeficient<0)
            cout<<'-';
        for(__int128 i=-1; i>=n.exponent; i--)
            p=p*10;
        if(n.coeficient<0)
            cout<<-n.coeficient/p<<'.';
        else
            cout<<n.coeficient/p<<'.';
        x=n.coeficient%p;
        while(x!=0)
        {
            x=x/10;
            ct--;
        }
        for(__int128 i=n.exponent;i<ct;i++)
            cout<<0;
        if(n.coeficient<0)
            cout<<-n.coeficient%p;
        else
            cout<<n.coeficient%p;
    }
    else if(n.exponent>=0)
    {
        cout<<n.coeficient;
        for(__int128 i=1; i<=n.exponent; i++)
            cout<<0;
    }
    cout<<" = "<<n.coeficient;
    if(n.exponent==INT128_MAX)
        cout<<" * cinf"<<endl;
    else if(n.exponent==INT128_MAX-1)
        cout<<" * 10 ^ "<< 1/0.0<<endl;
    else if(n.exponent==INT128_MIN)
        cout<<" * 10 ^ "<<-1/0.0<<endl;
    else
        cout<<" * 10 ^ "<<n.exponent<<endl;
}
bool InitializareFactorial = 0;                    /// Aceasta variabila retine daca valorile factorialelor au fost atribuite (1) sau nu (0)
                                                   /// This variable stores if the factorial values were assigned (1) or not (0)

int NrMaxFact = 33;                                /// Cel mai mare numar caruia pot sa ii calculez factorialul (33) | The biggest number that I can calculate its factorial (33)

__int128 FactorialVector[33 + 1];                  /// Vectorul care stocheaza factorialul fiecarui numar natural mai mic sau egal cu NrMaxFact (de la 0 la NrMaxFact sunt NrMaxFact + 1 elemente)
                                                   /// The vector which store factorial of each natural number between 0 and NrMaxFact (in total are NrMaxFact + 1 elements)

FormaStiintifica factorial(int n)                  /// Functia care returneaza factorialul unui numar si umple cu valori vectorului FactorialVector pe baza factorialului fiecarui numar
{                                                  /// The function which returns factorial of a number and put values on FactorialVector based on factorial of each number
    if(InitializareFactorial == 0)
    {
        __int128 p=1;                              /// p este factorialul indicelui i curent | p is the factorial for current index (i)
        FactorialVector[0]=1;
        for(int i=1;i<=NrMaxFact;i++)
        {
            p=p*i;
            FactorialVector[i]=p;
        }
        InitializareFactorial = 1;
    }
    FormaStiintifica nr;
    if(n>=0 && n<=NrMaxFact)
    {
        nr.coeficient = FactorialVector[n];        /// https://zeptomath.com/calculators/factorial.php
        nr.exponent = 0;
    }
    else if(n>NrMaxFact)
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
        nr.coeficient = 1;                         /// Returneaza infinitul complex (cinf = 1/0) in cazul factorialului unui numar negativ
        nr.exponent = INT128_MAX;                  /// Returns complex infinity (cinf = 1/0) if we want to return a factorial of a negative number
    }
    return nr;
}
FormaStiintifica div_int(Fractie fr)               /// In aceasta functie vrem sa returnam forma stiintifica a rezultatului real al lui x/y | This function returns scientific form of real result x/y
{
    long double nr;
    FormaStiintifica n;
    nr = (long double)fr.numarator/fr.numitor;
    n  = float_to_int(nr);
    return n;
}
Fractie int_div(FormaStiintifica n)
{
    Fractie f;
    f.numarator = n.coeficient;
    f.numitor = 1;
    if(n.coeficient == 0 && n.exponent == INT128_MAX)
    {
        f.numitor=0;
        return f;
    }
    while(n.exponent<0 && f.numarator != 0)
    {
        if(f.numitor <= (INT128_MAX) / 10 && f.numitor >= INT128_MIN / 10)
            f.numitor*=10;
        else
            f.numarator/=10;
        n.exponent+=1;
    }
    while(n.exponent>0 && f.numitor != 0)
    {
        if(f.numarator <= (INT128_MAX) / 10 && f.numarator >= INT128_MIN / 10)
            f.numarator*=10;
        else
            f.numitor/=10;
        n.exponent-=1;
    }
    return f;
}
FormaStiintifica CitireFormaStiintifica()
{
    FormaStiintifica f;
    f.coeficient = CitireNrIntreg();
    f.exponent   = CitireNrIntreg();
    while(f.coeficient%10==0 && f.coeficient!=0)   /// Daca numarul n e de forma 100*10^2, structura repetitiva va incerca sa faca sa fie de forma 1*10^4
    {                                              /// If n number is like 100*10^2, the repetitive structure tries to be like 1*10^4
        f.exponent++;
        f.coeficient/=10;
    }
    return f;
}
__int128 CMMDC (__int128 a, __int128 b)            /// https://www.pbinfo.ro/articole/73/cmmdc-si-cmmmc-algoritmul-lui-euclid
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
Fractie simplificare(Fractie n)
{
    bool ok = 0;
    if(n.numarator > 0 && n.numitor > 0)
    {
        n.numarator = -n.numarator;
        n.numitor   = -n.numitor;
    }
    else if(n.numarator > 0)
    {
        ok = 1;
        n.numarator = -n.numarator;
    }
    else if(n.numitor > 0)
    {
        ok = 1;
        n.numitor = -n.numitor;
    }
    __int128 cmmdc = CMMDC(n.numarator,n.numitor);
    n.numarator /= cmmdc;
    n.numitor   /= cmmdc;
    if(n.numarator != INT128_MIN && ok == 1)       /// __int128 nu poate retine -INT128_MIN | __int128 can't store -INT128_MIN
    {
        n.numarator = -n.numarator;
        ok = 0;
    }
    else if(n.numitor != INT128_MIN && ok == 1)
    {
        n.numitor = -n.numitor;
        ok = 0;
    }
    return n;
}
void AfisareFractie(Fractie f)
{
    cout<<f.numarator<<" / "<<f.numitor;
}
Fractie CitireFractie()
{
    Fractie n;
    n.numarator = CitireNrIntreg();
    n.numitor   = CitireNrIntreg();
    n = simplificare(n);
    if(debug == 1)
    {
        if(language == 0)
            cout<<"The fraction from the input is: ";
        else
            cout<<"Fractia citita este: ";
        AfisareFractie(n);
        cout<<endl;
    }
    return n;
}
void AcelasiNumitor(Fractie &a, Fractie &b)
{
    if(a.numitor != 0 && b.numitor != 0)
    {
        __int128 cmmdc = CMMDC(a.numitor,b.numitor);
        __int128 factor1 = a.numitor/cmmdc;
        __int128 factor2 = b.numitor/cmmdc;
        a.numarator *= factor2;
        a.numitor   *= factor2;
        b.numarator *= factor1;
        b.numitor   *= factor1;
    }
}
