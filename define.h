#include<iostream>
#include<vector>
#include<climits>
#include<complex>
#include<iomanip>
#include<iterator>
#include<algorithm>
#define LONGLONG_MAX (__int128)LLONG_MAX            /// https://stackoverflow.com/questions/18439520/is-there-a-128-bit-integer-in-c
#define LONGLONG_MIN (__int128)LLONG_MIN
#define INT128_MAX ((LONGLONG_MAX+1)*(LONGLONG_MAX+1)-1)*2+1
#define INT128_MIN LONGLONG_MIN * -LONGLONG_MIN * 2
#define pi "3.141592653589793238462643383279502884197"                                                              /// Definim constanta pi | Define constant pi
#define e  "2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274" /// Definim constanta e  | Define constant e
using namespace std;
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
