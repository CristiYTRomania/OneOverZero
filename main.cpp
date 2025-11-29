/// OneOverZero | Tested on GDB Online (C++ 23) and CodeBlocks 20.03 (Windows 10 si Ubuntu 22.04.5 LTS) | Testat pe GDB Online (C++ 23) si pe CodeBlocks 20.03 (Windows 10 and Ubuntu 22.04.5 LTS)
/// TODO: fractie+-*/^fractie, vectori de fractii si hexa (de forma ab.cd); log(fractie), log(hexa), e^fractie, e^hexa
///       fraction+-*/fraction, fraction vectors and hexadecimal number vectors (ab.cd); log(fraction), log(hexa), e^fraction, e^hexa
#include<cstdlib>                                                    /// Pentru atoi() | For atoi() -> Convert string to integer, atof(), rand(), srand() etc.
#include<climits>                                                    /// Pentru INT_MIN, INT_MAX, LONG_MIN etc. | For INT_MIN, INT_MAX, LONG_MIN etc.
#include<bits/stdc++.h>                                              /// Aici se afla toate bibliotecile        | Here are all the libraries
#include<iostream>                                                   /// Pentru cin si cout                     | For cin and cout         -> C++
#include<stdio.h>                                                    /// Pentru printf() si scanf()             | For printf() and scanf() -> C
#include<ctime>                                                      /// Pentru setarea seed-ului timpului actual pentru randomizer dinamic | For setting the actual time seed for dynamic randomizer
#include<cmath>                                                      /// Pentru functii matematice precum functia putere si modulul unui numar | For math functions like power and module functions
#include<complex>                                                    /// Numere complexe cu coeficienti reali         | Complex numbers with real coefficients
#include<fstream>                                                    /// Pentru a citi din fisiere si a scrie in ele  | To read and write files
#include "bigint.h"                                                  /// Integrarea operatorului de afisare pentru intregul pe 128 de biti | Cout operator integration of 128-bit integer
#include "hello.h"                                                   /// Numere complexe si functii vectoriale        | Complex numbers and vectorial functions
#define pi "3.141592653589793238462643383279502884197"                                                              /// Definim constanta pi | Define constant pi
#define e  "2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274" /// Definim constanta e  | Define constant e
using namespace std;                              /// Pentru cin si cout | For cin and cout -> C++
string Answer = "0";                              /// Ultimul rezultat al calculatorului virtual | The last answer of the virtual calculator
struct SolutiiComplexe
{
    complex<long double> x1,x2;
};
void ascii()                                      /// Afiseaza toate caracterele ASCII | Shows all ASCII characters
{
    for(int i=0;i<=26;i++)
        cout<<"char("<<i<<") = "<<char(i)<<"\n";
    cout<<"char(27) = ESC\n";
    for(int i=28;i<=282;i++)
        cout<<"char("<<i<<") = "<<char(i)<<"\n";
    cout<<"char(283) = ESC\n";
    for(int i=284;i<=511;i++)
        cout<<"char("<<i<<") = "<<char(i)<<"\n";
}
auto shift_bits(auto n, long long p)              /// Aceasta functie va shifta bitii unui numar in mod circular | This function will shift the bits in circular way
{
    int dimensiune = sizeof(n) * 8;
    bool b;
    while(p>0)
        p-=dimensiune;
    while(p<0)
        p+=dimensiune;
    while(p>0)                                    /// Shiftare circulara la dreapta cu un pas | Circular shifting to the right with one step
    {
        b=n%2;
        n=n>>1;
        if(b==0)
            n=n & (((long long)1<<(dimensiune-1))^(-1));
        else if(b==1)
            n=n |  ((long long)1<<(dimensiune-1));
        p--;
    }
    while(p<0)                                    /// Shiftare circulara la stanga  cu un pas | Circular shifting to the left  with one step
    {
        b=(n>>(dimensiune-1))&1;
        n=n<<1;
        n=n|b;
        p++;
    }
    return n;
}
void math_game(bool language)                     /// Acesta este un joc in romana si engleza in care va trebui sa punem raspunsul corect pentru niste operatii aritmetice
{
    srand(time(0));
    int level=1,n,x,y,total,correct;
    string s;
    bool ok=1;
    while(ok==1)
    {
        correct=0;
        if(level>=1 and level<=5)
            total=5;
        else if(level==6)
            total=6;
        if(language==1)
            cout<<"Nivelul "<<level<<endl;
        else if(language==0)
            cout<<"Level "<<level<<endl;
        while(level>=1 and level<=6)
        {
            cin>>s;
            if(s=="quit" or s=="exit")
            {
                ok=0;
                break;
            }
            else if(s=="help")
            {
                cout<<"Help options: \n"<<"'play' for playing; \n"<<"'quit' (or 'exit') for quitting the game. \n";
            }
            else if(s=="play")
            {
                if(level>=0 and level<=5)
                {
                    x=rand()%(level*2+1);
                    y=rand()%(level*2+1);
                }
                else if(level==6)
                {
                    x=rand()%21;
                    y=rand()%21;
                }
                cout<<x<<" + "<<y<<" = ";
                cin>>n;
                if(x+y==n)
                {
                    correct++;
                    cout<<"Correct answer! (";
                }
                else
                    cout<<"Wrong answer! (";
                cout<<correct<<"/"<<total<<")\n";
            }
            if(correct==total)
            {
                if(level<6)
                {
                    level++;
                    cout<<"You reached level "<<level<<"! \n";
                }
                else
                {
                    cout<<"Level 7 coming soon! \n";
                    level=1;
                    ok=0;
                }
            }
        }
        if(level<1 and level>6)
            level=1;
    }
}
double f(double x, unsigned int n, double v[])    /// Returnam rezultatul unui polinom de grad, x si coeficienti cunoscuti
{
    double s=0,p=1;
    for(unsigned int i=0;i<=n;i++)
    {
        s=s+p*v[i];
        p=p*x;
    }
    return s;
}
double frecventa(string c, long long n)           /// Functia care returneaza frecventa unei note muzicale | This functions returns musical note's frequency
{
    double p=pow(2,n-7),f=0/0.0;
         if(c=="A" ||c=="a")f=3520*p;
    else if(c=="G#"||c=="g#"||c=="Ab"||c=="ab")f=3322*p;
    else if(c=="G" ||c=="g")f=3136*p;
    else if(c=="F#"||c=="f#"||c=="Gb"||c=="gb")f=2960*p;
    else if(c=="F" ||c=="f" ||c=="E#"||c=="e#")f=2794*p;
    else if(c=="E" ||c=="e" ||c=="Fb"||c=="fb")f=2637*p;
    else if(c=="D#"||c=="d#"||c=="Eb"||c=="eb")f=2489*p;
    else if(c=="D" ||c=="d")f=2349*p;
    else if(c=="C#"||c=="c#"||c=="Db"||c=="db")f=2217*p;
    else if(c=="C" ||c=="c" ||c=="B#"||c=="b#")f=2093*p;
    else if(c=="B" ||c=="b" ||c=="Cb"||c=="cb")f=3951*p;
    else if(c=="A#"||c=="a#"||c=="Bb"||c=="bb")f=3729*p;
    return f;
}
void afisare_memorie(unsigned long long n)
{
    if       (n<1024)
        cout<<n<<" bytes | ";
    else if  (n<1024*1024)
        cout<<n/1024.0<<" KiB | ";
    else if  (n<1024*1024*1024)
        cout<<n/1024.0/1024.0<<" MiB | ";
    else if  (n<(long long)1024*1024*1024*1024)
        cout<<n/1024.0/1024.0/1024.0<<" GiB | ";
    else
        cout<<n/1024.0/1024.0/1024.0/1024.0<<" TiB | ";
}
SolutiiComplexe ecuatie(long double a,long double b,long double c)
{
    SolutiiComplexe solutie;
    if(a!=0)
    {
        complex<long double> delta=b*b-4*a*c;
        delta=sqrt(delta);
        solutie.x1=(-b+delta)/(2*a);
        solutie.x2=(-b-delta)/(2*a);
    }
    else if(b!=0)
        solutie.x1=solutie.x2=-c/b;
    else
        solutie.x1=solutie.x2=0/0.0;
    return solutie;
}
string operatie(string a="0", string b="0", string operator_="-")              /// Pentru a+b si a-b | For a+b and a-b
{                                  /// TODO: In cazul in care a-b,a,b>=0 | When a-b,a,b>=0 (Nu am implementat 0,(3) si +-inf/cinf/nan | Didn't implement 0.3 with 3 repeating and +-inf/cinf/nan)
    string rezultat,capat;         /// TODO: Am uitat sa sterg 0 de la stanga si de la dreapta la final | I forgot to delete 0 from the left and the right (01.110)
    unsigned long long punct1 = a.find("."), punct2 = b.find("."); /// TODO: As putea pune if-urile cu nan, inf si cinf in functie | I can put the ifs with nan, inf and cinf in this function
    if(punct1==string::npos)
        a.append(".0"), punct1 = a.find(".");
    if(punct2==string::npos)
        b.append(".0"), punct2 = b.find(".");
    string zero="0";
    bool ok=0;
    if(punct1<punct2)
        for(unsigned long long i=punct1;i<punct2;i++)
        {
            zero.append(a);
            a=zero;
            zero="0";
        }
    else if(punct1>punct2)
        for(unsigned long long i=punct2;i<punct1;i++)
        {
            zero.append(b);
            b=zero;
            zero="0";
        }
    punct1=a.length();
    punct2=b.length();
    if(punct1<punct2)
    {
        for(unsigned long long i=punct1;i<punct2;i++)
            a.append("0");
        punct1=punct2;
    }
    else if(punct1>punct2)
        for(unsigned long long i=punct2;i<punct1;i++)
            b.append("0");
    for(unsigned long long i=punct1-1;i<punct1;i--)
    {
        if(a[i]>='0'&&a[i]<='9')
        {
            int nr;
            if(operator_=="-")
                nr=a[i]-b[i]-ok;
            else if(operator_=="+")
                nr=a[i]+b[i]+ok-96;
            ok=0;
            if(nr<0)
            {
                nr+=10;
                ok=1;
            }
            else if(nr>9)
            {
                nr-=10;
                ok=1;
            }
            capat=to_string(nr);
        }
        else
            capat=".";
        capat.append(rezultat);
        rezultat=capat;
    }
    if(ok==1&&operator_=="+")
    {
        string unu="1";
        unu.append(rezultat);
        rezultat=unu;
    }
    if(operator_=="+"||operator_=="-")
        return rezultat;
    else
        return "nan";
}
struct perecheCantor
{
    long long x,y;
};
long long bijectieCantor(perecheCantor n)
{
    long long suma=n.x+n.y;
    return (suma*(suma+1))/2+n.y;
}
perecheCantor bijectieCantor(long long n)
{
    perecheCantor n1;
    long long p=0;
    while((p*(p+1))/2<=n)
        p++;
    p--;
    n1.y=n-(p*(p+1))/2;
    n1.x=p-n1.y;
    return n1;
}
string convertire(string a)
{
    if(a=="pi")
        a=pi;
    else if(a=="e")
        a=e;
    else if(a=="a" || a=="ans" || a=="answer" || a=="rez" || a=="rezultat")
        a=Answer;
    return a;
}
void afisare_linii()
{
    for(int i=1;i<=80;i++)
        cout<<"-";
    cout<<endl;
}
struct Hexazecimal
{
    long long a;
    unsigned long long b,c,d;
};
Hexazecimal citire_hexa()
{
    Hexazecimal n;
    cout<<"0xAB.CD (-2^63 <= A <= 2^63 - 1; 0 <= B, C, D <= 2^64 - 1)"<<endl<<"A = ";
    cin>>n.a;
    cout<<"B = ";
    cin>>n.b;
    cout<<"C = ";
    cin>>n.c;
    cout<<"D = ";
    cin>>n.d;
    return n;
}
void afisare_hexa(Hexazecimal n)
{
    cout<<n.a<<" * 2^64 + "<<n.b<<" * 2^0 + "<<n.c<<" * 2^-64 + "<<n.d<<" * 2^-128 = \n";
    cout << showbase      /// afiseaza prefixul 0x          | show the 0x prefix
         << internal      /// acopera intre prefix si numar | fill between the prefix and the number
         << setfill('0'); /// acopera cu cifre de 0         | fill with 0s
    cout << hex << setw(18) << n.a << noshowbase << setw(16) << n.b << '.' << setw(16) << n.c << setw(16) << n.d << endl << setw(0) << dec;
    /**
        https://cplusplus.com/reference/ios/showbase/
        https://cplusplus.com/forum/windows/51591/     -> Afiseaza toate cele 16 cifre ale numarului in baza 16 | Showing all 16 digits of a hexadecimal number
    */
}
void CalcAnswer(string s)
{
    Answer = s;
    cout << s;
}
int main()
{
    bool ok=1;                                    /// Daca ok este 1, programul va rula, daca ok este 0, programul se va incheia | If ok=1, the program will run. If not, the program will stop
    string s;
    ifstream fin("memory.txt");
    int partitii;
    fin>>partitii;
    string nume_partitie[partitii];
    unsigned long long mem_totala[partitii],mem_libera[partitii],MEM_TOTALA=0,MEM_LIBERA=0;
    for(int i=0;i<partitii;i++)
    {
        fin>>nume_partitie[i]>>mem_totala[i]>>mem_libera[i];
        int nr_caractere=nume_partitie[i].length();
        for(int j=1;j<=11-nr_caractere;j++)
            nume_partitie[i].append(" ");
        MEM_TOTALA+=mem_totala[i];
        MEM_LIBERA+=mem_libera[i];
    }
    for(int i=0;i<partitii-1;i++)
        for(int j=i+1;j<partitii;j++)
            if(mem_libera[i]<mem_libera[j])
            {
                swap(mem_libera[i],mem_libera[j]);
                swap(mem_totala[i],mem_totala[j]);
                swap(nume_partitie[i],nume_partitie[j]);
            }
    while(ok==1)
    {
        cout<<"Type 'help' for instructions! \n";
        cout<<"Introduceti 'ajutor' pentru instructiuni! \n";
        afisare_linii();
        cout<<fixed<<setprecision(30)<<"Meniu principal | Main: ";   /// Suntem in meniul principal | We are in the main menu
        cin>>s;
        int nr_caractere=s.length();                       /// Numarul de caractere al comenzii citite de la tastatura | The string length command of the keyboard input
        for(int i=0;i<nr_caractere;i++)                    /// Transformam orice litera mare din comanda in litera mica pentru ca comanda sa nu fie case sensitive
            if(s[i]>='A' && s[i]<='Z')                     /// We convert any uppercase letter in the command to lowercase so that the command to be not case sensitive.
                s[i]+=32;
        if(s=="game")                                      /// Jocul de matematica in limba engleza | Math game in English  language
            math_game(0);
        else if(s=="joc")                                  /// Jocul de matematica in limba romana  | Math game in Romanian language
            math_game(1);
        else if(s=="quit" or s=="exit" or s=="iesire")     /// Iesire din program                   | Exiting the program
            ok=0;
        else if(s=="f" or s=="function" or s=="functie")   /// Apelarea functiei polinomiale        | Calling polinomial function
        {
            double x;
            unsigned int n;
            cout<<"x = ";
            cin>>x;
            cout<<"n = ";
            cin>>n;
            double v[n+1];
            for(unsigned int i=n;i<=n;i--)
            {
                cout<<"a["<<i<<"] = ";
                cin>>v[i];
            }
            for(unsigned int i=n;i>0;i--)
                cout<<v[i]<<" * x^"<<i<<" + ";
            cout<<v[0]<<" * x^0 = "<<f(x,n,v)<<endl;
        }
        else if(s=="help")                                 /// Comanda "help"   va genera comenzile in limba engleza | "help"   command will generate the commands in English  language
        {
            cout<<"Help options: \n"<<"'game' for starting the game; \n"<<"'quit' (or 'exit') for quitting the app; \n";
        }
        else if(s=="ajutor")                               /// Comanda "ajutor" va genera comenzile in limba romana  | "ajutor" command will generate the commands in Romanian language
        {
            cout<<"Optiuni pentru ajutor: \n"<<"'iesire' pentru iesirea din aplicatie; \n"<<"'joc' pentru a incepe jocul; \n";
        }
        else if(s=="numere" or s=="numbers")               /// Aceasta comanda va genera cateva numere si simboluri in ordine crescatoare, marginile fiind predominate de infinitul complex
        {                                                  /// This command will generate some numbers and symbols in in ascending order,  the edges being dominated by complex infinity
            printf("%s %s %d %d %d %d %d %d %d %d %d %d %s ","cinf","-inf",-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,"-0.0");
            printf("%d %s %d %d %d %d %d %d %d %d %d %d %s %s \n",0,"0.0",1,2,3,4,5,6,7,8,9,10,"inf","cinf");
        }
        else if(s=="ascii")                                /// Apelam functia ce va afisa toate caracterele ASCII | Calling the function which shows all ASCII characters
            ascii();
        else if(s=="frecventa" or s=="frequency")          /// Apelam functia care returneaza frecventa unei note muzicale citite de la tastatura
        {                                                  /// Calling the function which returns musical note's frequency, which is read from the keyboard
            long long n;
            string c;
            cout<<"Nota din octava: ";
            cin>>c;
            cout<<"Octava: ";
            cin>>n;
            cout<<frecventa(c,n)<<" Hz"<<endl;
        }
        else if(s=="pi-e")
        {
            cout<<"pi - e =  "<<pi<<endl;
            cout<<"       -  "<<e <<endl;
            cout<<"       =  "<<operatie(pi,e,"-")<<endl;
            cout<<"       ~= "<<stold(pi)-stold(e)<<endl;  /// Aici afisam rezultatul scaderii lui pi la e | This shows result of pi - e
        }
        else if(s=="no"||s=="no."||s=="number")
        {
            string n;
            cout<<"Enter the real number: ";
            cin>>n;
            float       real_float      =stof (n);
            double      real_double     =stod (n);
            long double real_long_double=stold(n);
            if(real_double<=INT_MAX&&real_double>=INT_MIN)
                cout<<"The value stored in int                is: "    <<stoi(n)         <<" | "<<sizeof(stoi(n))         <<" bytes"<<endl;
            else
                cout<<"The value can't be stored in int"               <<endl;
            if(real_long_double<=ULLONG_MAX&&-real_long_double<=ULLONG_MAX)
                cout<<"The value stored in unsigned long long is: "    <<stoull(n)       <<" | "<<sizeof(stoull(n))       <<" bytes"<<endl;
            else
                cout<<"The value can't be stored in unsigned long long"<<endl;
            if(real_long_double<=LLONG_MAX&&real_long_double>=LLONG_MIN)
                cout<<"The value stored in long long          is: "    <<stoll(n)        <<" | "<<sizeof(stoll(n))        <<" bytes"<<endl;
            else
                cout<<"The value can't be stored in long long"         <<endl;
            cout<<"The value stored in float              is: "        <<real_float      <<" | "<<sizeof(real_float)      <<" bytes"<<endl;
            cout<<"The value stored in double             is: "        <<real_double     <<" | "<<sizeof(real_double)     <<" bytes"<<endl;
            cout<<"The value stored in long double        is: "        <<real_long_double<<" | "<<sizeof(real_long_double)<<" bytes"<<endl;
            cout<<"The difference between the values stored in double      and float  is: "     <<real_double-real_float            <<endl;
            cout<<"The difference between the values stored in long double and double is: "     <<real_long_double-real_double      <<endl;
            cout<<"The value stored in float represented in scientific notation is: ";
            show_floated_int(float_to_int(real_float));
            cout<<"The value stored in double represented in scientific notation is: ";
            show_floated_int(float_to_int(real_double));
            cout<<"The value stored in long double represented in scientific notation is: ";
            show_floated_int(float_to_int(real_long_double));
        }
        else if(s=="nr"||s=="nr."||s=="numar")
        {
            string n;
            cout<<"Introduceti numarul real: ";
            cin>>n;
            float       real_float      =stof (n);
            double      real_double     =stod (n);
            long double real_long_double=stold(n);
            if(real_double<=INT_MAX&&real_double>=INT_MIN)
                cout<<"Valoarea stocata in int                este: "     <<stoi(n)         <<" | "<<sizeof(stoi(n))         <<" bytes"<<endl;
            else
                cout<<"Valoarea nu poate fi stocata in int"               <<endl;
            if(real_long_double<=ULLONG_MAX&&real_long_double>=-ULLONG_MAX)
                cout<<"Valoarea stocata in unsigned long long este: "     <<stoull(n)       <<" | "<<sizeof(stoull(n))       <<" bytes"<<endl;
            else
                cout<<"Valoarea nu poate fi stocata in unsigned long long"<<endl;
            if(real_long_double<=LLONG_MAX&&real_long_double>=LLONG_MIN)
                cout<<"Valoarea stocata in long long este:          "     <<stoll(n)        <<" | "<<sizeof(stoll(n))        <<" bytes"<<endl;
            else
                cout<<"Valoarea nu poate fi stocata in long long"         <<endl;
            cout    <<"Valoarea stocata in float              este: "     <<real_float      <<" | "<<sizeof(real_float)      <<" bytes"<<endl;
            cout    <<"Valoarea stocata in double             este: "     <<real_double     <<" | "<<sizeof(real_double)     <<" bytes"<<endl;
            cout    <<"Valoarea stocata in long double        este: "     <<real_long_double<<" | "<<sizeof(real_long_double)<<" bytes"<<endl;
            cout    <<"Diferenta dintre valorile stocate in double, respectiv float, este:       " <<real_double-real_float            <<endl;
            cout    <<"Diferenta dintre valorile stocate in long double, respectiv double, este: " <<real_long_double-real_double      <<endl;
            cout<<"Valoarea stocata in float reprezentata in forma stiintifica este: ";
            show_floated_int(float_to_int(real_float));
            cout<<"Valoarea stocata in double reprezentata in forma stiintifica este: ";
            show_floated_int(float_to_int(real_double));
            cout<<"Valoarea stocata in long double   reprezentata in forma stiintifica este: ";
            show_floated_int(float_to_int(real_long_double));
        }
        else if(s == "div" || s == "division" || s == "impartire")
        {
            string a;
            Fractie n;                                                       /// https://stackoverflow.com/questions/18439520/is-there-a-128-bit-integer-in-c
            cin>>a;
            n.numarator=StringToInt(a);
            cin>>a;
            n.numitor=StringToInt(a);
            FormaStiintifica x = div_int(n);                                 /// Apelez functia care returneaza forma stiintifica a rezultatului real al lui x/y
                                                                             /// Calling the funtion which returns scientific form of real result of x/y
            show_floated_int(x);                                             /// Afiseaza forma stiinfica a numarului real: coeficient  * 10^exponent
        }                                                                    /// Shows the scientific form of  real number: coefficient * 10^exponent
        else if(s=="shift")
        {
            long long n,p;
            cin>>n>>p;
            n=shift_bits(n,p);                             /// Aici vrem sa shiftam la dreapta cu p biti numarul n | Here we want to shift the number n with p bits to the right
            cout<<n<<" ("<<sizeof(shift_bits(n,p))<<" bytes)"<<endl;
        }
        else if(s=="ecuatie")
        {
            long double a,b,c;
            cout<<"a = ";
            cin>>a;
            cout<<"b = ";
            cin>>b;
            cout<<"c = ";
            cin>>c;
            SolutiiComplexe solutie=ecuatie(a,b,c);
            cout<<a<<" * x^2 + "<<b<<" * x^1 + "<<c<<" * x^0 = 0"<<endl;
            cout<<"x[1] = "<<solutie.x1<<endl;
            cout<<"x[2] = "<<solutie.x2<<endl;
        }
        else if(s=="calculator"||s=="calc")   /// TODO: sa nu fie case sensitive a si b; operatori noi: ^, sqrt(), log() | To not be case sensitive (a and b); New operators: ^, sqrt(), log()
        {
            string a,b,operator_;
            cin>>a>>operator_>>b;
            a=convertire(a);
            b=convertire(b);
            if(operator_=="+")
            {
                if(a=="cinf"&&b=="cinf")
                    CalcAnswer("nan");
                else if(a=="nan"||b=="nan")
                    CalcAnswer("nan");
                else if(a=="inf"&&b=="-inf")
                    CalcAnswer("nan");
                else if(a=="-inf"&&b=="inf")
                    CalcAnswer("nan");
                else if(a=="inf"||a=="-inf")
                    CalcAnswer(a);
                else if(b=="inf"||b=="-inf")
                    CalcAnswer(b);
                else
                {
                    Answer = operatie(a,b,"+");
                    cout<<Answer<<" ~= "<<stold(a)+stold(b);
                }
            }
            else if(operator_=="-")
            {
                if(a=="cinf"&&b=="cinf")
                    CalcAnswer("nan");
                else if(a=="nan"||b=="nan")
                    CalcAnswer("nan");
                else if(a=="inf"&&b=="inf")
                    CalcAnswer("nan");
                else if(a=="-inf"&&b=="-inf")
                    CalcAnswer("nan");
                else if(a=="inf"||a=="-inf")
                    CalcAnswer(a);
                else if(b=="inf")
                    CalcAnswer("-inf");
                else if(b=="-inf")
                    CalcAnswer("inf");
                else
                {
                    Answer = operatie(a,b,"-");
                    cout<<Answer<<" ~= "<<stold(a)-stold(b);
                }
            }
            else if(operator_=="*")
            {
                if(a=="nan"||b=="nan")
                    CalcAnswer("nan");
                else if(a=="cinf"&&b=="0")
                    CalcAnswer("nan");
                else if(a=="0"&&b=="cinf")
                    CalcAnswer("nan");
                else if(a=="cinf"||b=="cinf")
                    CalcAnswer("cinf");
                else if(a=="0"||b=="0")
                    CalcAnswer("0");
                else
                    CalcAnswer( to_string(stold(a)*stold(b)) );
            }
            else if(operator_=="/"||operator_=="//")
            {
                if(a=="nan"||b=="nan")
                    CalcAnswer("nan");
                else if(a=="cinf"&&b=="cinf")
                    CalcAnswer("nan");
                else if(b=="cinf")
                    CalcAnswer("0");
                else if(a=="cinf")
                    CalcAnswer("cinf");
                else if(a=="0"&&b=="0")
                    CalcAnswer("nan");
                else if(b=="0")
                    CalcAnswer("cinf");
                else if(a=="0")
                    CalcAnswer("0");
                else if(operator_=="/")
                    CalcAnswer( to_string(stold(a)/stold(b)) );
                else if(operator_=="//")
                    CalcAnswer( to_string(floor(stold(a)/stold(b))) );
            }
            else if(operator_=="%")
            {
                if(a=="nan"||b=="nan")
                    CalcAnswer("nan");
                else if(a=="cinf"&&b=="cinf")
                    CalcAnswer("nan");
                else if(b=="cinf")
                    CalcAnswer(a);
                else if(a=="cinf")
                    CalcAnswer("nan");
                else if(a=="0"&&b=="0")
                    CalcAnswer("nan");
                else if(b=="0")
                    CalcAnswer("nan");
                else if(a=="0")
                    CalcAnswer("0");
                else if(a=="inf"||a=="-inf")
                    CalcAnswer("nan");
                else if(b=="inf"||b=="-inf")
                    CalcAnswer(a);
                else if(b=="0.0"||b=="-0.0"||b=="-0")
                    CalcAnswer("nan");
                else if(a=="0.0"||a=="-0.0"||a=="-0")
                    CalcAnswer(a);
                else
                    CalcAnswer( to_string(stoll(a)%stoll(b)) );
            }
            cout<<endl;
        }
        else if(s=="hexadecimal"||s=="hex"||s=="hexa")
        {
            Hexazecimal n;
            n=citire_hexa();
            afisare_hexa(n);
        }
        else if(s=="disk"||s=="memory"||s=="partition"||s=="partitions")
        {
            cout<<endl<<"Nume partitie | Memorie totala | Memorie libera | Memorie utilizata | Procent utilizat"<<endl<<endl;
            for(int i=0;i<partitii;i++)
            {
                unsigned long long mem_utilizata=mem_totala[i]-mem_libera[i];
                cout<<nume_partitie[i]<<" | ";
                afisare_memorie(mem_totala[i]);
                afisare_memorie(mem_libera[i]);
                afisare_memorie(mem_utilizata);
                cout<<(long double)mem_utilizata/mem_totala[i]*100<<'%'<<endl;
            }
            cout    <<endl<<"Total       | ";
            afisare_memorie(MEM_TOTALA);
            afisare_memorie(MEM_LIBERA);
            afisare_memorie(MEM_TOTALA-MEM_LIBERA);
            cout<<(long double)(MEM_TOTALA-MEM_LIBERA)/MEM_TOTALA*100<<'%'<<endl;
        }
        else if(s=="complex"||s=="inf"||s=="infinity")
        {
            complex<string> a((string)"4",(string)"5");
            complex<long double> b=4.0+5i;
            cout<<fixed<<a<<' '<<b<<' '<<typeid(a).name()<<endl;
            cout<<" inf -> Positive Infinity (1/+0.0)"<<endl;
            cout<<"-inf -> Negative Infinity (1/-0.0)"<<endl;
            cout<<"cinf -> Complex  Infinity (1/0)"<<endl;
            cout<<" nan -> Not A Number      (0/0)"<<endl;
        }
        else if(s=="bijectie"||s=="cantor")
        {
            /**
                Algoritmul bijectiei lui Cantor predat de catre domnul profesor Gabriel Istrate la Facultatea de Matematica si Informatica din Bucuresti, la seminarul de Calculabilitate
                si Complexitate

                Cantor's bijection algorithm taught by Professor Gabriel Istrate at the Faculty of Mathematics and Computer Science in Bucharest, at the Computability and Complexity seminar
            */
            perecheCantor n;
            cin>>n.x>>n.y;
            long long n1=bijectieCantor(n);
            cout<<n1<<": ";
            n=bijectieCantor(n1);
            cout<<n.x<<' '<<n.y<<endl;
        }
        else if(s=="hello")
        {
            printf("Hello, World! \n");
            main2();
        }
        else if(s=="factorial" || s=="fact")
        {
            int n;
            cin>>n;
            FormaStiintifica f;
            f = factorial(n);
            show_floated_int(f);
        }
        else if(s=="fractie" || s=="fraction")
        {
            FormaStiintifica f;
            string a;
            cin>>a;
            f.coeficient=StringToInt(a);
            cin>>a;
            f.exponent=StringToInt(a);
            Fractie fr = int_div(f);
            cout<<fr.numarator<<'/'<<fr.numitor<<endl;
        }
        else
            cout<<"Comanda necunoscuta | Unknown command \n";
        afisare_linii();
    }
    return 0; /// Se va inchide programul si se va returna valoarea 0 | The program will close and the value returned will be 0
}
