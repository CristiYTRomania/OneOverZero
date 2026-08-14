#include "variable.h"
#include "games.h"
#include "piano.h"
using namespace std;
struct ComplexSolutions
{
    complex<long double> x1,x2;
};
complex<long double> CinComplexNumber()
{
    long double a,b;
    cout<<"a = ";
    a = CinRealNumber();
    cout<<"b = ";
    b = CinRealNumber();
    complex<long double> n(a,b);
    return n;
}
template<typename T>
void CoutComplexNumber(complex<T> n)
{
    CoutRealNumber(real(n));
    cout<<" + ";
    CoutRealNumber(imag(n));
    cout<<" * i";
}
template<typename T>
auto circular_shift_bits(T n, long long p)
{
    if(typeid(n)==typeid(bool))
        return n;
    else if(typeid(n)==typeid(double)||typeid(n)==typeid(float)||typeid(n)==typeid(long double))
    {
        cout<<"Incompatible type: "<<typeid(n).name()<<endl;
        return n;
    }
    int dimension = sizeof(n) * 8;
    bool b;
    while(p>dimension)
        p-=dimension;
    while(p<-dimension)
        p+=dimension;
    while(p>0)
    {
        b=n%2;
        n=n>>1;
        if(b==0)
            n=n & (((long long)1<<(dimension-1))^(-1));
        else if(b==1)
            n=n |  ((long long)1<<(dimension-1));
        p--;
    }
    while(p<0)
    {
        b=(n>>(dimension-1))&1;
        n=n<<1;
        n=n|b;
        p++;
    }
    return n;
}
long double f(long double x, unsigned int n, long double v[])
{
    long double s=0,p=1;
    for(unsigned int i=0;i<=n;i++)
    {
        if(v[i] != 0)
            s=s+p*v[i];
        p=p*x;
        if(i==(unsigned int)INT_MAX*2+1)
            break;
    }
    return s;
}
void display_memory(unsigned long long n)
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
ComplexSolutions equation(long double a,long double b,long double c)
{
    ComplexSolutions solution;
    if(a!=0)
    {
        complex<long double> delta=b*b-4*a*c;
        delta=sqrt(delta);
        solution.x1=(-b+delta)/(2*a);
        solution.x2=(-b-delta)/(2*a);
    }
    else if(b!=0)
        solution.x1=solution.x2=-c/b;
    else
        solution.x1=solution.x2=0/0.0;
    return solution;
}
string operation(string a="0", string b="0", string operator_="-")
{                      /// TODO: In cazul in care a-b,a,b>=0 | When a-b,a,b>=0 (Nu am implementat 0,(3) si +-inf/cinf/nan | Didn't implement 0.3 with 3 repeating and +-inf/cinf/nan)
    string result,chr; /// TODO: Am uitat sa sterg 0 de la stanga si de la dreapta la final | I forgot to delete 0 from the left and the right (01.110)
    unsigned long long point1 = a.find("."), point2 = b.find("."); /// TODO: As putea pune if-urile cu nan, inf si cinf in functie | I can put the ifs with nan, inf and cinf in this function
    if(point1==string::npos)
        a.append(".0"), point1 = a.find(".");
    if(point2==string::npos)
        b.append(".0"), point2 = b.find(".");
    string zero="0";
    bool ok=0;
    if(point1<point2)
        for(unsigned long long i=point1;i<point2;i++)
        {
            zero.append(a);
            a=zero;
            zero="0";
        }
    else if(point1>point2)
        for(unsigned long long i=point2;i<point1;i++)
        {
            zero.append(b);
            b=zero;
            zero="0";
        }
    point1=a.length();
    point2=b.length();
    if(point1<point2)
    {
        for(unsigned long long i=point1;i<point2;i++)
            a.append("0");
        point1=point2;
    }
    else if(point1>point2)
        for(unsigned long long i=point2;i<point1;i++)
            b.append("0");
    for(unsigned long long i=point1-1;i<point1;i--)
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
            chr=to_string(nr);
        }
        else
            chr=".";
        chr.append(result);
        result=chr;
    }
    if(ok==1&&operator_=="+")
    {
        string one="1";
        one.append(result);
        result=one;
    }
    if(operator_=="+"||operator_=="-")
        return result;
    else
        return "nan";
}
FractionOld operation(FractionOld a, FractionOld b, string operator_="+")
{
    FractionOld result;
    if(operator_=="+")
    {
        SameDenominator(a,b);
        if(a.denominator != 0 && b.denominator != 0)
        {
            result.numerator   = a.numerator + b.numerator;
            result.denominator = a.denominator;
        }
        else if(a.denominator == 0 && b.denominator == 0)
        {
            result.numerator=0;
            result.denominator=0;
        }
        else if(a.denominator==0)
        {
            result.numerator=a.numerator;
            result.denominator=0;
        }
        else if(b.denominator==0)
        {
            result.numerator=b.numerator;
            result.denominator=0;
        }
    }
    else if(operator_=="-")
    {
        SameDenominator(a,b);
        if(a.denominator != 0 && b.denominator != 0)
        {
            result.numerator   = a.numerator - b.numerator;
            result.denominator = a.denominator;
        }
        else if(a.denominator == 0 && b.denominator == 0)
        {
            result.numerator=0;
            result.denominator=0;
        }
        else if(a.denominator==0)
        {
            result.numerator=a.numerator;
            result.denominator=0;
        }
        else if(b.denominator==0)
        {
            result.numerator=-b.numerator;
            result.denominator=0;
        }
    }
    else if(operator_=="*")
    {
        result.numerator   = a.numerator * b.numerator;
        result.denominator = a.denominator   * b.denominator;
    }
    else if(operator_=="/")
    {
        result.numerator   = a.numerator * b.denominator;
        result.denominator = a.denominator   * b.numerator;
    }
    else if(operator_=="^")
    {
        long double exponent = 1.0/b.denominator,
                    power1 = pow((long double)a.numerator,  (long double)b.numerator),
                    power2 = pow((long double)a.denominator,(long double)b.numerator),
                    numerator   = pow((long double)power1,  (long double)exponent),
                    denominator = pow((long double)power2,  (long double)exponent),
                    ratio_ = numerator / denominator;
        ScientificForm n = float_to_int(ratio_);
        result = int_div(n);
    }
    else
    {
        result.numerator=0;
        result.denominator=0;
    }
    result = simplification(result);
    return result;
}
struct CantorPair
{
    long long x,y;
};
long long CantorBijection(CantorPair n)
{
    long long sum=n.x+n.y;
    return (sum*(sum+1))/2+n.y;
}
CantorPair CantorBijection(long long n)
{
    CantorPair n1;
    long long p=0;
    while((p*(p+1))/2<=n)
        p++;
    p--;
    n1.y=n-(p*(p+1))/2;
    n1.x=p-n1.y;
    return n1;
}
struct Hexadecimal
{
    long long a;
    unsigned long long b,c,d;
};
Hexadecimal CinHexadecimal()
{
    Hexadecimal n;
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
void CoutHexadecimal(Hexadecimal n)
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
bool lHospital(long double v[], unsigned int n)
{
    bool ok=0;
    if(v[0] != 0)
        ok=1;
    v[0] = 0;
    for(unsigned int i=1;i<=n;i++)
    {
        if(v[i] != 0)
            ok=1;
        v[i-1] = v[i] * i;
        v[i] = 0;
        if(i==0)
            break;
    }
    return ok;
}
int main()
{
    string s;
    ifstream fin("memory.txt");
    int partitions;
    fin>>partitions;
    string PartitionName[partitions];
    unsigned long long total_memory[partitions],free_memory[partitions],TOTAL_MEMORY=0,FREE_MEMORY=0;
    cout<<fixed;
    for(int i=0;i<partitions;i++)
    {
        fin>>PartitionName[i]>>total_memory[i]>>free_memory[i];
        int string_length=PartitionName[i].length();
        for(int j=1;j<=11-string_length;j++)
            PartitionName[i].append(" ");
        TOTAL_MEMORY+=total_memory[i];
        FREE_MEMORY+=free_memory[i];
    }
    for(int i=0;i<partitions-1;i++)
        for(int j=i+1;j<partitions;j++)
            if(free_memory[i]<free_memory[j])
            {
                swap(free_memory[i],free_memory[j]);
                swap(total_memory[i],total_memory[j]);
                swap(PartitionName[i],PartitionName[j]);
            }
    StartProgram(0);
    while(1)
    {
        cout<<endl;
        cout<<"> ";
        cin>>s;
        s = NotCaseSensitive(s);
        if(s=="game")                                      /// Jocul de matematica in limba engleza | Math game in English  language
            math_game(0);
        else if(s=="joc")                                  /// Jocul de matematica in limba romana  | Math game in Romanian language
            math_game(1);
        else if(s=="quit" or s=="exit" or s=="iesire")     /// Iesire din program                   | Exiting the program
            break;
        else if(s=="f" or s=="function" or s=="functie")   /// Apelarea functiei polinomiale        | Calling polynomial function
        {
            long double x;
            unsigned int n;
            cout<<"x = ";
            x=CinRealNumber();
            cout<<"n = ";
            cin>>n;
            long double v[n+1];
            for(unsigned int i=n;i<=n;i--)
            {
                cout<<"a["<<i<<"] = ";
                v[i]=CinRealNumber();
                if(i==0)
                    break;
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
        else if(s=="numere"||s=="numbers"||s=="inf"||s=="infinity") /// Aceasta comanda va genera cateva numere si simboluri in ordine crescatoare, marginile fiind predominate de infinitul complex
        {                                                  /// This command will generate some numbers and symbols in in ascending order,  the edges being dominated by complex infinity
            printf("%s %s %d %d %d %d %d %d %d %d %d %d %s ","cinf","-inf",-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,"-0.0");
            printf("%d %s %d %d %d %d %d %d %d %d %d %d %s %s \n",0,"0.0",1,2,3,4,5,6,7,8,9,10,"inf","cinf");
            cout<<" inf -> Positive Infinity (1/+0.0)"<<endl;
            cout<<"-inf -> Negative Infinity (1/-0.0)"<<endl;
            cout<<"cinf -> Complex  Infinity (1/0)"<<endl;
            cout<<" nan -> Not A Number      (0/0)"<<endl;

            complex<string> a((string)"4",(string)"5");
            cout<<a<<endl;
            complex<long double> c=0.0+1i;
            cout<<c<<endl;
            long double mic = nextafter((long double)0.0, (long double)1.0);    /// https://stackoverflow.com/questions/39746861/is-dbl-min-the-smallest-positive-double
            CoutRealNumber(mic,10*1000);
            cout<<endl;
            complex<__int128> aa(5,4);CoutComplexNumber(aa+aa);cout<<endl;
            complex<long double>a2,a3(1/.0,3);a2=complex<long double>(6/.0,7); CoutComplexNumber(a2);cout<<endl<<(a2 == a3)<<endl;CoutComplexNumber(a3);cout<<endl;
        }
        else if(s=="ascii")
            ascii();
        else if(s=="frecventa" or s=="frequency")
            frequency();
        else if(s=="no"||s=="no."||s=="number")
        {
            string n;
            cout<<"Enter the real number: ";
            cin>>n;
            n = conversion(n);
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
            n = conversion(n);
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
            FractionOld n;
            n = CinFraction();
            ScientificForm x = div_int(n);                                   /// Apelez functia care returneaza forma stiintifica a rezultatului real al lui x/y
                                                                             /// Calling the funtion which returns scientific form of real result of x/y
            show_floated_int(x);                                             /// Afiseaza forma stiinfica a numarului real: coeficient  * 10^exponent
        }                                                                    /// Shows the scientific form of  real number: coefficient * 10^exponent
        else if(s=="shift"||s=="circular"||s=="circularshift"||s=="circular_shift")
        {
            long long n, p;
            cin>>n>>p;
            n=circular_shift_bits(n,p);                    /// Aici vrem sa shiftam la dreapta cu p biti numarul n | Here we want to shift the number n with p bits to the right
            cout<<n<<" ("<<sizeof(circular_shift_bits(n,p))<<" bytes)"<<endl;
        }
        else if(s=="ecuatie"||s=="equation")
        {
            long double a,b,c;
            cout<<"a = ";
            cin>>a;
            cout<<"b = ";
            cin>>b;
            cout<<"c = ";
            cin>>c;
            ComplexSolutions solution=equation(a,b,c);
            CoutRealNumber(a);
            cout<<" * x^2 + ";
            CoutRealNumber(b);
            cout<<" * x^1 + ";
            CoutRealNumber(c);
            cout<<" * x^0 = 0"<<endl;
            cout<<"x[1] = ";
            CoutComplexNumber(solution.x1);
            cout<<endl;
            cout<<"x[2] = ";
            CoutComplexNumber(solution.x2);
            cout<<endl;
        }
        else if(s=="calculator"||s=="calc")                /// TODO: Operatori noi: ^, sqrt(), log() | New operators: ^, sqrt(), log()
        {
            string a,b,operator_;
            cin>>a>>operator_>>b;
            a=conversion(a);
            b=conversion(b);
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
                    Answer = operation(a,b,"+");
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
                    Answer = operation(a,b,"-");
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
            Hexadecimal n;
            n=CinHexadecimal();
            CoutHexadecimal(n);
        }
        else if(s=="disk"||s=="memory"||s=="partition"||s=="partitions"||s=="partitii"||s=="memorie"||s=="disc")
        {
            cout<<endl<<"Nume partitie | Memorie totala | Memorie libera | Memorie utilizata | Procent utilizat"<<endl<<endl;
            for(int i=0;i<partitions;i++)
            {
                unsigned long long used_memory=total_memory[i]-free_memory[i];
                cout<<PartitionName[i]<<" | ";
                display_memory(total_memory[i]);
                display_memory(free_memory[i]);
                display_memory(used_memory);
                cout<<(long double)used_memory/total_memory[i]*100<<'%'<<endl;
            }
            cout    <<endl<<"Total       | ";
            display_memory(TOTAL_MEMORY);
            display_memory(FREE_MEMORY);
            display_memory(TOTAL_MEMORY-FREE_MEMORY);
            cout<<(long double)(TOTAL_MEMORY-FREE_MEMORY)/TOTAL_MEMORY*100<<'%'<<endl;
        }
        else if(s=="complex")                              /// TODO: complex<string>
        {
            complex<long double> c;
            c = CinComplexNumber();
            CoutComplexNumber(c);
            cout<<endl;
        }
        else if(s=="bijectie"||s=="cantor")
        {
            /**
                Algoritmul bijectiei lui Cantor predat de catre domnul profesor Gabriel Istrate la Facultatea de Matematica si Informatica din Bucuresti, la seminarul de Calculabilitate
                si Complexitate

                Cantor's bijection algorithm taught by Professor Gabriel Istrate at the Faculty of Mathematics and Computer Science in Bucharest, at the Computability and Complexity seminar
            */
            CantorPair n;
            cin>>n.x>>n.y;
            long long n1=CantorBijection(n);
            cout<<n1<<": ";
            n=CantorBijection(n1);
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
            ScientificForm f;
            f = factorial(n);
            show_floated_int(f);
        }
        else if(s=="fractie" || s=="fraction")
        {
            ScientificForm f;
            f = CinScientificForm();
            FractionOld fr = int_div(f);
            CoutFraction(fr);
            cout<<endl;
        }
        else if(s=="polynomialratio"||s=="polynomial_ratio"||s=="raport"||s=="poli"||s=="polinomial"||s=="poly"||s=="polynomial"||s=="ratio"||s=="polinomialraport"||s=="polinomial_raport")
        {
            long double x,numerator,denominator;
            unsigned int n1,n2;
            cout<<"x = ";
            x=CinRealNumber();
            cout<<"n[1] = ";
            cin>>n1;
            cout<<"n[2] = ";
            cin>>n2;
            long double a[n1+1],b[n2+1];
            for(unsigned int i=n1;i<=n1;i--)
            {
                cout<<"a["<<i<<"] = ";
                a[i]=CinRealNumber();
                if(i==0)
                    break;
            }
            for(unsigned int i=n2;i<=n2;i--)
            {
                cout<<"b["<<i<<"] = ";
                b[i]=CinRealNumber();
                if(i==0)
                    break;
            }
            cout<<"( ";
            for(unsigned int i=n1;i>0;i--)
            {
                CoutRealNumber(a[i]);
                cout<<" * x^"<<i<<" + ";
            }
            CoutRealNumber(a[0]);
            cout<<" * x^0 ) / ( ";
            for(unsigned int i=n2;i>0;i--)
            {
                CoutRealNumber(b[i]);
                cout<<" * x^"<<i<<" + ";
            }
            CoutRealNumber(b[0]);
            cout<<" * x^0 ) = ";
            numerator=f(x,n1,a);
            denominator  =f(x,n2,b);
            while( (1/numerator==0 && 1/denominator==0) || (numerator==0 && denominator==0) )
            {
                bool ok1 = lHospital(a,n1);
                bool ok2 = lHospital(b,n2);
                numerator=f(x,n1,a);
                denominator  =f(x,n2,b);
                if(ok1==0 && ok2==0)
                    break;
            }
            CoutRealNumber(numerator);
            cout<<" / ";
            CoutRealNumber(denominator);
            cout<<" = ";
            CoutRealNumber(numerator/denominator);
            cout<<endl;
        }
        else if(s=="fractii"||s=="fractions")
        {
            FractionOld a, b;
            string operator_;
            a=CinFraction();
            cin>>operator_;
            b=CinFraction();
            FractionOld rez = operation(a,b,operator_);
            cout<<"( ";
            CoutFraction(a);
            cout<<" ) "<<operator_<<" ( ";
            CoutFraction(b);
            cout<<" ) = ";
            CoutFraction(rez);
            cout<<endl;
        }
        else if(s=="language")
        {
            language = 1 - language;
            if(language == 0)
                cout<<"Language set to English! \n";
            else
                cout<<"Language set to Romanian! \n";
        }
        else if(s=="limba")
        {
            language = 1 - language;
            if(language == 0)
                cout<<"Limba setata este limba engleza! \n";
            else
                cout<<"Limba setata este limba romana! \n";
        }
        else if(s=="romanian"||s=="romana")
        {
            language = 1;
            if(s=="romana")
                cout<<"Limba setata este limba romana! \n";
            else
                cout<<"Language set to Romanian! \n";
        }
        else if(s=="english"||s=="engleza")
        {
            language = 0;
            if(s=="engleza")
                cout<<"Limba setata este limba engleza! \n";
            else
                cout<<"Language set to English! \n";
        }
        else if(s=="debug" || s=="debugging")
        {
            debug = 1 - debug;
            if(language == 0)
            {
                cout<<"Debug mode ";
                if(debug == 1)
                    cout<<"enabled! \n";
                else
                    cout<<"disabled! \n";
            }
            else
            {
                cout<<"Modul de debugging ";
                if(debug == 1)
                    cout<<"activat! \n";
                else
                    cout<<"dezactivat! \n";
            }
        }
        else if(s=="cmmdc"||s=="gcd")
        {
            __int128 a, b;
            a = CinIntNumber();
            b = CinIntNumber();
            cout<<GCD(a,b)<<endl;
        }
        else if(s=="cmmmc"||s=="lcm")
        {
            __int128 a, b;
            a = CinIntNumber();
            b = CinIntNumber();
            cout<<a/GCD(a,b)*b<<endl;
        }
        else if(s=="clear"||s=="cls")
        {
            StartProgram(1);
        }
        else if(s=="variabila")
        {
            show_variable(attribute_variable("ro"));
            cout<<endl;
        }
        else if(s=="variable" || s=="var")
        {
            show_variable(attribute_variable("en"));
            cout<<endl;
        }
        else
        {
            cout<<CinRealNumber();
        }
    }
    return 0;
}
