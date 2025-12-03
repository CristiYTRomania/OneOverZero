#include<iostream>
#include<vector>
#include<climits>
#include<complex>
#include<iomanip>
#include<iterator>
#include<algorithm>
#include<bits/stdc++.h>                                              /// Aici se afla toate bibliotecile        | Here are all the libraries
#include<cstdlib>                                                    /// Pentru atoi() | For atoi() -> Convert string to integer, atof(), rand(), srand() etc.
#include<climits>                                                    /// Pentru INT_MIN, INT_MAX, LONG_MIN etc. | For INT_MIN, INT_MAX, LONG_MIN etc.
#include<iostream>                                                   /// Pentru cin si cout                     | For cin and cout         -> C++
#include<stdio.h>                                                    /// Pentru printf() si scanf()             | For printf() and scanf() -> C
#include<ctime>                                                      /// Pentru setarea seed-ului timpului actual pentru randomizer dinamic | For setting the actual time seed for dynamic randomizer
#include<cmath>                                                      /// Pentru functii matematice precum functia putere si modulul unui numar | For math functions like power and module functions
#include<complex>                                                    /// Numere complexe cu coeficienti reali         | Complex numbers with real coefficients
#include<fstream>                                                    /// Pentru a citi din fisiere si a scrie in ele  | To read and write files
#define LONGLONG_MAX (__int128)LLONG_MAX                             /// https://stackoverflow.com/questions/18439520/is-there-a-128-bit-integer-in-c
#define LONGLONG_MIN (__int128)LLONG_MIN
#define INT128_MAX ((LONGLONG_MAX+1)*(LONGLONG_MAX+1)-1)*2+1
#define INT128_MIN LONGLONG_MIN * -LONGLONG_MIN * 2
#define pi "3.141592653589793238462643383279502884197"                                                              /// Definim constanta pi | Define constant pi
#define e  "2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274" /// Definim constanta e  | Define constant e
bool debug = 0, language = 0;
using namespace std;
string Answer = "0";                                /// Ultimul rezultat al calculatorului virtual | The last answer of the virtual calculator
int main2()
{
	vector<complex<long double>> v;                 /// Numere complexe si functii vectoriale | Complex numbers and vectorial functions
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
