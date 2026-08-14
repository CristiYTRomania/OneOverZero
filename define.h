#include<bits/stdc++.h>
#define LONGLONG_MAX (__int128)LLONG_MAX                             /// https://stackoverflow.com/questions/18439520/is-there-a-128-bit-integer-in-c
#define LONGLONG_MIN (__int128)LLONG_MIN
#define INT128_MAX ( ((LONGLONG_MAX+1)*(LONGLONG_MAX+1)-1)*2+1 )
#define INT128_MIN ( LONGLONG_MIN * -LONGLONG_MIN * 2 )
#define INF  INT128_MAX
#define CINF INT128_MIN
#define MINF (INT128_MIN+1)
#define PI    attribute_variable(pi)
#define Euler attribute_variable(e)
#define Pi "3.141592653589793238462643383279502884197..."
#define E  "2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274..."
bool debug = 0, language = 0;
using namespace std;
string Answer = "0";
template <typename T> int sgn(T val) {              /// https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
    return (T(0) < val) - (val < T(0));
}
string NotCaseSensitive(string s)
{
    int string_length=s.length();
    for(int i=0;i<string_length;i++)
        if(s[i]>='A' && s[i]<='Z')
            s[i]+=32;
    return s;
}
string conversion(string a)
{
    a = NotCaseSensitive(a);
    if(a=="pi")
        a="3.141592653589793238462643383279502884197";
    else if(a=="e")
        a="2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274";
    else if(a=="a" || a=="ans" || a=="answer" || a=="rez" || a=="rezultat")
        a=Answer;
    else if(a=="infinity")
        a="inf";
    else if(a=="-infinity")
        a="-inf";
    else if(a=="complex_infinity"||a=="cinfinity"||a=="complexinfinity")
        a="cinf";
    else if(a=="english"||a=="engleza")
        a="en";
    else if(a=="romanian"||a=="romana")
        a="ro";
    return a;
}
long double CinRealNumber(string language="en")
{
    string n;
    long double x;
    cin>>n;
    n = conversion(n);
    if(n=="cinf")
    {
        if(language == "ro")
            cout<<"Precizie pierduta! cinf convertit la inf";
        else
            cout<<"Precision loss! cinf converted to inf";
        cout<<endl;
        x=stold("inf");
    }
    else
        x=stold(n);
    return x;
}
void ascii()
{
    for(int i=0;i<=511;i++)
    {
        if(i==27||i==283)
        {
            cout<<"char("<<i<<") = ESC\n";
            continue;
        }
        cout<<"char("<<i<<") = "<<char(i)<<"\n";
    }
}
int main2()
{
	vector<complex<long double>> v;
	complex<long double>sum = 0;
	vector<complex<long double>>::iterator it;
	v.push_back((long double)0);
	v.push_back((long double)LLONG_MAX);
	size_t n = v.size();                            /// size_t = unsigned long long
	for (auto& x : v)
		x += (long double)LLONG_MAX;
	cout << fixed;
	for (auto x : v)
		cout << x << ' ';
	reverse(v.begin(), v.end());
	cout << endl;
	for (it = v.begin(); it != v.end(); it++)
	{
		cout << *it << ' ';
		sum += *it;
	}
	cout << endl << "Media numerelor este: " << sum / (long double)n << endl;
	cout << "1/0 = " << complex<long double>(1,0) / (long double)0 << endl;
	cout << "0/0 = " << complex<long double>(0,0) / (long double)0 << endl;
	cout << "LLONG_MAX = " << *find(v.begin(), v.end(), (long double)LLONG_MAX) << endl;
	cout << "Exista LLONG_MAX: " << (find(v.begin(), v.end(), (long double)LLONG_MAX) != v.end());
	cout<<" (TRUE)"<<endl;
	return 0;
}
