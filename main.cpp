#include<cstdlib>                                                    /// Pentru atoi() | For atoi() -> Convert string to integer, atof(), rand(), srand() etc.
#include<climits>                                                    /// Pentru INT_MIN, INT_MAX, LONG_MIN etc. | For INT_MIN, INT_MAX, LONG_MIN etc.
#include<bits/stdc++.h>                                              /// Aici se afla toate bibliotecile        | Here are all the libraries
#include<iostream>                                                   /// Pentru cin si cout         | For cin and cout         -> C++
#include<stdio.h>                                                    /// Pentru printf() si scanf() | For printf() and scanf() -> C
#include<ctime>                                                      /// Pentru setarea seed-ului timpului actual pentru randomizer dinamic | For setting the actual time seed for dynamic randomizer
#include<cmath>                                                      /// Pentru functii matematice precum functia putere si modulul unui numar | For math functions like power and module functions
#include<complex>                                                                                                   /// Numere complexe cu coeficienti reali | Complex numbers with real coefficients
#include<fstream>                                                                                                   /// Pentru a citi din fisiere si a scrie in ele | To read and write files
#define pi 3.141592653589793238462643383279502884197                                                                /// Definim constanta pi   | Define constant pi
#define e 2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274    /// Definim constanta e    | Define constant e
using namespace std;                              /// Pentru cin si cout | For cin and cout -> C++
long long FactorialVector[22];                    /// Vectorul care stocheaza factorialul fiecarui numar natural mai mic sau egal cu 20 (de la 0 la 20 sunt 21 de elemente)
                                                  /// The vector which store factorial of each natural number between 0 and 20 (in total are 21 elements)
long long factorial(int n)                        /// Functia care returneaza factorialul unui numar si umple cu valori vectorului FactorialVector pe baza factorialului fiecarui numar
{                                                 /// The function which returns factorial of a number and put values on FactorialVector based on factorial of each number
    if(FactorialVector[21]==0)                    /// Ultimul element al vectorului retine daca valorile factorialelor au fost atribuite (1) sau nu (0)
    {                                             /// The last element from the vector stores if the factorial values were assigned (1) or not (0)
        long long p=1;                            /// p este factorialul indicelui i curent | p is the factorial for current index (i)
        FactorialVector[0]=1;
        for(int i=1;i<=20;i++)
        {
            p=p*i;
            FactorialVector[i]=p;
        }
        FactorialVector[21]=1;
    }
    if(n>=0 && n<=20)
        return FactorialVector[n];
    else
        return LONG_LONG_MIN;                     /// Returneaza (long long)(1/0.0) in cazul factorialului unui numar negativ si in cazul returnarii unui numar care va genera overflow
}                                                 /// Returns (long long)(1/0.0) if we want to return a factorial of a negative number or a number that generates overflow
struct FormaStiintifica                           /// Structura reprezinta forma stiintifica a unui numar real (x*10^y), cu coeficientul si exponentul numere intregi de tip long long
{                                                 /// This structure returns scientific form of a real number  (x*10^y), with coefficient and exponent which are long long integers
    long long coeficient,exponent,numitor,shiftari;                  /// numaratorul = coeficient
};
FormaStiintifica float_to_int(long double f)      /// Returneaza forma stiintifica a unui numar real | Return scientific form of a real number
{
    FormaStiintifica n;
    n.exponent=0;
    while(f!=(long long)f                         /// Ca sa extragem zecimalele din numarul real intr-un intreg            | To extract decimals from real number to a integer
          && f*10<=LLONG_MAX && f*10>=LLONG_MIN)  /// Ca sa nu dea underflow sau overflow                                  | To not get overflow or underflow
    {
        f*=10;
        n.exponent--;
    }
    if(f==1/0.0||f==-1/0.0)
    {
        n.exponent=LLONG_MAX-1;
        n.coeficient=1;
    }
    while(f>LLONG_MAX||f<LLONG_MIN)
    {
        f/=10;
        n.exponent++;
    }
    n.coeficient=f;
    while(n.coeficient%10==0 && n.coeficient!=0)  /// Daca numarul n e de forma 100*10^2, structura repetitiva va incerca sa faca sa fie de forma 1*10^4
    {                                             /// If n number is like 100*10^2, the repetitive structure tries to be like 1*10^4
        n.exponent++;
        n.coeficient/=10;
    }
    return n;
}
FormaStiintifica div_int(long long x,long long y) /// In aceasta functie vrem sa returnam forma stiintifica a rezultatului real al lui x/y | This function returns scientific form of real result x/y
{
    FormaStiintifica n1;
    long long n,p,ct;
    n1.exponent=0;
    if(y==0)
    {
        n1.coeficient=x;
        n1.exponent=LLONG_MAX;
    }
    else
    {
        for(long long i=2; i<=x or i<=y; i++)
        {
            while(y%i==0)
            {
                if(x%i==0)
                    x=x/i;
                else
                {
                    p=1;
                    n=i;
                    ct=0;
                    while(n!=0)
                    {
                        p=p*10;
                        ct++;
                        n=n/10;
                    }
                    x=x*p/i;
                    n1.exponent-=ct;
                }
                y=y/i;
            }
        }
        while(x%10==0 and x!=0)
        {
            n1.exponent++;
            x=x/10;
        }
        n1.coeficient=x;
    }
    return n1;
}
void show_floated_int(FormaStiintifica n)         /// Afiseaza forma stiinfica a numarului real   | Shows scientific form of real number
{
    long long p=1,x,ct=0;
    if(n.exponent==LLONG_MAX)                     /// In loc de x*10^y este x impartit la 0       | Instead of x*10^y is x over 0
    {
        if(n.coeficient==0)
            cout<<0/0.0;
        else
            cout<<"cinf";
    }
    else if(n.exponent==LLONG_MAX-1)              /// In loc de x*10^y este x inmultit cu infinit | Instead of x*10^y is x times infinity
    {
        if(n.coeficient==0)
            cout<<0;
        else
            cout<<n.coeficient/0.0;
    }
    else if(n.exponent==LLONG_MIN)                /// In loc de x*10^y este x impartit la infinit | Instead of x*10^y is x over infinity
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
        for(long long i=-1; i>=n.exponent; i--)
            p=p*10;
        cout<<n.coeficient/p<<'.';
        x=n.coeficient%p;
        while(x!=0)
        {
            x=x/10;
            ct--;
        }
        for(long long i=n.exponent;i<ct;i++)
            cout<<0;
        cout<<abs(n.coeficient%p);
    }
    else if(n.exponent>=0)
    {
        cout<<n.coeficient;
        for(long long i=1; i<=n.exponent; i++)
            cout<<0;
    }
    cout<<" = "<<n.coeficient;
    if(n.exponent==LLONG_MAX)
        cout<<" * cinf"<<endl;
    else if(n.exponent==LLONG_MAX-1)
        cout<<" * 10 ^ "<< 1/0.0<<endl;
    else if(n.exponent==LLONG_MIN)
        cout<<" * 10 ^ "<<-1/0.0<<endl;
    else
        cout<<" * 10 ^ "<<n.exponent<<endl;
}
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
FormaStiintifica shift_bits(FormaStiintifica n, long long p)  /// Aceasta functie va shifta bitii unui numar in mod circular | This function will shift the bits in circular way
{
    bool b;
    n.shiftari+=p;
    while(p>0)                                    /// Shiftare circulara la dreapta cu un pas | Circular shifting to the right with one step
    {
        b=n.coeficient%2;
        n.coeficient=n.coeficient>>1;
        if(b==0)
            n.coeficient=n.coeficient & (((long long)1<<63)^(-1));
        else if(b==1)
            n.coeficient=n.coeficient |  ((long long)1<<63);
        p--;
    }
    while(p<0)                                    /// Shiftare circulara la stanga  cu un pas | Circular shifting to the left  with one step
    {
        b=(n.coeficient>>63)&1;
        n.coeficient=n.coeficient<<1;
        n.coeficient=n.coeficient|b;
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
int main()
{
    bool ok=1;                                    /// Daca ok este 1, programul va rula, daca ok este 0, programul se va incheia | If ok=1, the program will run. If not, the program will stop
    string s;
    cout<<"Type 'help' for instructions! \n";
    cout<<"Introduceti 'ajutor' pentru instructiuni! \n";
    while(ok==1)
    {
        cout<<endl<<"Meniu principal | Main: ";            /// Suntem in meniul principal           | We are in the main menu
        cin>>s;
        int nr_caractere=s.length();                       /// Numarul de caractere al comenzii citite de la tastatura | The string length command of the keyboard input
        for(int i=0;i<nr_caractere;i++)                    /// Transformam orice litera mare din comanda in litera mica pentru ca comanda sa nu fie case sensitive
            if(s[i]>='A'&&s[i]<='Z')                       /// We convert any uppercase letter in the command to lowercase so that the command to be not case sensitive.
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
            cin>>x>>n;
            double v[n+1];
            for(unsigned int i=n;i>=0;i++)
                cin>>v[i];
            cout<<f(x,n,v)<<endl;
        }
        else if(s=="help")                                 /// Comanda "help"   va genera comenzile in limba engleza | "help"   command will generate the commands in English  language
            cout<<"Help options: \n"<<"'game' for starting the game; \n"<<"'quit' (or 'exit') for quitting the app; \n";
        else if(s=="ajutor")                               /// Comanda "ajutor" va genera comenzile in limba romana  | "ajutor" command will generate the commands in Romanian language
            cout<<"Optiuni pentru ajutor: \n"<<"'iesire' pentru iesirea din aplicatie; \n"<<"'joc' pentru a incepe jocul; \n";
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
            cout<<"pi - e = "<<pi<<" - "<<e<<" = "<<pi-e<<endl;    /// Aici afisam rezultatul scaderii lui pi la e | This shows result of pi - e
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
            if(real_long_double<=ULLONG_MAX&&real_long_double>=-ULLONG_MAX)
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
            cout<<"The difference between the values stored in double      and float  is: " <<real_double-real_float            <<endl;
            cout<<"The difference between the values stored in long double and double is: " <<real_long_double-real_double      <<endl;
            cout<<"The value stored in float       represented in scientific notation is: ";
            show_floated_int(float_to_int(real_float));
            cout<<"The value stored in double      represented in scientific notation is: ";
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
            cout<<"Valoarea stocata in float         reprezentata in forma stiintifica este: "; /// TO DO: identare + translate + comentarii + github
            show_floated_int(float_to_int(real_float));
            cout<<"Valoarea stocata in double        reprezentata in forma stiintifica este: "; /// int/int, complex, hexa si cout fixed setprecision, de scris definitii int_max,long_max etc.
            show_floated_int(float_to_int(real_double));
            cout<<"Valoarea stocata in long double   reprezentata in forma stiintifica este: ";
            show_floated_int(float_to_int(real_long_double));
        }
        else if(s=="div")
        {
            FormaStiintifica n;
            long long x,y;
            cin>>x>>y;
            n=div_int(x,y);                                /// Apelez functia care returneaza forma stiintifica a rezultatului real al lui x/y
                                                           /// Calling the funtion which returns scientific form of real result of x/y
            show_floated_int(n);                           /// Afiseaza forma stiinfica a numarului real: coeficient  * 10^exponent
        }                                                  /// Shows the scientific form of  real number: coefficient * 10^exponent
        else if(s=="shift")
        {
            FormaStiintifica n;
            long long p;
            n.shiftari=0;
            cin>>n.coeficient>>p;
            n=shift_bits(n,p);                             /// Aici vrem sa shiftam la dreapta cu p biti numarul n care deja a fost shiftat anterior cu p2 biti la dreapta
            cout<<n.coeficient<<' '<<n.shiftari<<endl;
            cin>>p;
            n=shift_bits(n,p);                             /// Here we want to shift the number n with p bits to the right, which has been shifted before with p2 bits tot the right
            cout<<n.coeficient<<' '<<n.shiftari<<endl;
        }
    } /// TO DO: calculator cu char, int, float, double, real, intreg etc., de forma a+b, cu a si b sa fie char, functia eval() si sa verific proiectul in codeblocks 20.03, programiz si onlinegdb
    /**
    baze de date in fisiere                           -> prima data o sa facem in fisiere text
    intreg/int 5                                      -> citim textul "intreg" si dupa aceea numarul intreg 5
    ecuatii grad 1 si 2                               -> de facut ecuatii de gradele 1 si 2 (coeficientii numere reale si solutiile numere complexe)
    **/


    return 0; /// Se va inchide programul si se va returna valoarea 0 | The program will close and the value returned will be 0
}
