#include "bigint.h"
using namespace std;
enum variable_type
{
    Integer=0,
    e,
    pi,
    Imaginary,
    Scientific=100,
    Power,
    Aleph,
    Real=200,
    Complex,
};
const int var_length = 100;
struct variable
{
    long double real[2];
    __int128 intreg[2];
    variable_type tip;
    string name;
}vars[var_length];
enum showing_type
{
    Exact,
    Decimal
};
template<typename T1, typename T2>
variable attribute_variable(variable_type tip, T1 nr1, T2 nr2, string name="", string language="en")
{
    variable var;
    language = conversion(language);
    var.tip  = tip;
    var.name = name;
    if(tip==Real or tip==Complex)
    {
        var.real[0] = nr1;
        var.real[1] = nr2;
    }
    else
    {
        var.intreg[0] = nr1;
        if(tip==Aleph && var.intreg[0]<0)
            var.intreg[0]=0;
        var.intreg[1] = nr2;
    }
    if(name=="")
    {
        return var;
    }
    bool found=0;
    int p=-1;
    for(int i=0; i<var_length && found==0; i++)
    {
        if(vars[i].name==name)
        {
            found=1;
            p=i;
        }
    }
    for(int i=0; i<var_length && found==0; i++)
    {
        if(vars[i].name=="")
        {
            found=1;
            p=i;
        }
    }
    if(found==0)
    {
        if(language=="ro")
            cout<<"Nu mai exista spatiu pentru crearea unei noi variabile! \n";
        else
            cout<<"A new variable can't be created because the storage is full! \n";
        return var;
    }
    vars[p]=var;
    return var;
}
variable attribute_variable(variable_type tip, string name="", string language="en")
{
    variable var;
    var.tip = tip;
    bool nr1=1,nr2=1;
    if(var.tip==Aleph || var.tip==Complex || var.tip==Real)
        nr1=nr2=0;
    else if(var.tip==Scientific)
        nr2=0;
    var=attribute_variable(tip,nr1,nr2,name,language);
    return var;
}
template<typename T>
variable attribute_variable(variable_type tip, T nr1, string name="", string language="en")
{
    variable var;
    var.tip = tip;
    bool nr2=1;
    if(var.tip==Aleph || var.tip==Complex || var.tip==Real || var.tip==Scientific)
        nr2=0;
    var=attribute_variable(tip,nr1,nr2,name,language);
    return var;
}
variable attribute_variable(string language="en")
{
    language=conversion(language);
    variable var;
    if(language=="ro")
        cout<<"Introduceti numele noii variabile: ";
    else
        cout<<"Enter the name of the new variable: ";
    string name;
    cin>>name;
    if(language=="ro")
        cout<<"Introduceti tipul de variabila ";
    else
        cout<<"Enter the type of the new variable ";
    cout<<"(Integer, e, pi, Imaginary, Scientific, Power, Aleph, Real, Complex): ";
    string tip_string;
    cin>>tip_string;
    variable_type tip;
    if(tip_string=="integer"||tip_string=="Integer"||tip_string=="int"||tip_string=="Int")
        tip=Integer;
    else if(tip_string=="e"||tip_string=="E")
        tip=e;
    else if(tip_string=="pi"||tip_string=="PI"||tip_string=="Pi")
        tip=pi;
    else if(tip_string=="i"||tip_string=="I"||tip_string=="Imaginary"||tip_string=="imaginary")
        tip=Imaginary;
    else if(tip_string=="Scientific"||tip_string=="scientific")
        tip=Scientific;
    else if(tip_string=="Power"||tip_string=="power"||tip_string=="Pow"||tip_string=="pow")
        tip=Power;
    else if(tip_string=="Aleph"||tip_string=="aleph")
        tip=Aleph;
    else if(tip_string=="Real"||tip_string=="real")
        tip=Real;
    else if(tip_string=="Complex"||tip_string=="complex"||tip_string=="Comp"||tip_string=="comp")
        tip=Complex;
    else
        return var;
    if(language=="ro")
        cout<<"Structura numarului va fi de forma: ";
    else
        cout<<"The structure of the number will be: ";
    if(tip==Integer)
        cout<<"x / y";
    else if(tip==e)
        cout<<"e * x / y";
    else if(tip==pi)
        cout<<"pi * x / y";
    else if(tip==Imaginary)
        cout<<"i * x / y";
    else if(tip==Scientific)
        cout<<"x * 10 ^ y";
    else if(tip==Power)
        cout<<"x ^ y";
    else if(tip==Aleph)
        cout<<"Aleph_x * (-1) ^ y";
    else if(tip==Real)
        cout<<"x + sqrt(y)";
    else if(tip==Complex)
        cout<<"x + y * i";
    cout<<endl;
    if(language=="ro")
        cout<<"Introduceti cele 2 numere x si y: ";
    else
        cout<<"Enter the 2 numbers x and y: ";
    if(tip==Real||tip==Complex)
    {
        long double x, y;
        cin>>x>>y;
        var=attribute_variable(tip,x,y,name,language);
    }
    else
    {
        __int128 x, y;
        x=CinIntNumber();
        y=CinIntNumber();
        var=attribute_variable(tip,x,y,name,language);
    }
    return var;
}
void show_variable(variable var, showing_type y = Exact)
{
    if(var.tip>=Integer && var.tip<Scientific)
    {
        if(var.intreg[0]==0 && var.intreg[1]==0)
            cout<<"nan";
        else if(var.intreg[0] == 0)
            cout<<0;
        else if(var.intreg[1] == 0)
            cout<<"cinf";
        else if(y == Exact)
        {
            string coefficient="";
            if(var.tip==Imaginary)
                coefficient="i";
            else if(var.tip==e)
                coefficient="e";
            else if(var.tip==pi)
                coefficient="pi";
            else if(var.tip==Integer)
                coefficient="1";
            else
                return;
            if(var.intreg[0] != var.intreg[1])
                coefficient+=" * ";
            if(var.tip!=Integer)
                cout<<coefficient;
            if(var.intreg[0] == var.intreg[1]);
            else if(var.intreg[1] == 1)
                cout<<var.intreg[0];
            else
                cout<<var.intreg[0]<<" / "<<var.intreg[1];
        }
        else if(y == Decimal)
        {
            if(var.tip==pi)
            {
                if(var.intreg[0] == var.intreg[1])
                    cout<<Pi;
                else
                    cout<<stold(Pi)*(var.intreg[0]/var.intreg[1]);
            }
            else if(var.tip==e)
            {
                if(var.intreg[0] == var.intreg[1])
                    cout<<E;
                else
                    cout<<stold(E)*(var.intreg[0]/var.intreg[1]);
            }
            else if(var.tip==Imaginary)
            {
                if(var.intreg[0] == var.intreg[1])
                    cout<<"i";
                else if(var.intreg[1] == 1)
                    cout<<"i * "<<var.intreg[0];
                else
                    cout<<"i * "<<(long double)var.intreg[0]/var.intreg[1];
            }
        }
        else
            return;
    }
    else if(var.tip==Real)
        if(var.real[1] >= 0)
            CoutRealNumber( var.real[0]+sqrt(var.real[1]) );
        else
        {
            cout<<"i * ";
            CoutRealNumber(sqrt(-var.real[1]));
            cout<<" + ";
            CoutRealNumber(var.real[0]);
        }
    else if(var.tip==Complex)
    {
        __int128 intreg0=int(var.real[0]);
        __int128 intreg1=int(var.real[1]);
        if(var.real[0]==intreg0 && intreg0!=0)
            cout<<intreg0;
        else
            cout<<var.real[0];
        cout<<" + i * ";
        if(var.real[1]==intreg1 && intreg1!=0)
            cout<<intreg1;
        else
            cout<<var.real[1];
    }
    else if(var.tip==Scientific)
    {

    }
    else if(var.tip==Aleph)
    {

    }
    else if(var.tip==Power)
    {

    }
    else
        return;
}
int compare(variable var1, variable var2, bool show=0)
{
    if(var1.tip == Integer && var2.tip == Integer)
        if(var1.intreg[1] == 0 || var2.intreg[1] == 0)
        {
            if(show==1)
                cout<<var1.intreg[0]<<" / "<<var1.intreg[1]<<" != "<<var2.intreg[0]<<" / "<<var2.intreg[1];
            return -1;
        }
        else
            return (var1.intreg[0]*var2.intreg[1] > var2.intreg[0]*var1.intreg[1]) - (var2.intreg[0]*var1.intreg[1] > var1.intreg[0]*var2.intreg[1]);
    else
        return 0;
}
