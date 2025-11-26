#include<iostream>
#include<vector>
#include<climits>
#include<complex>
#include<iomanip>
#include<iterator>
#include<algorithm>
using namespace std;
int main2()
{
	vector<complex<long double>> v;
	complex<long double>sum = 0;
	vector<complex<long double>>::iterator it;
	v.push_back((long double)0);
	v.push_back((long double)LLONG_MAX);
	size_t n = v.size(); /// size_t = unsigned long long
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
	cout << "1/0 = " << sum / (long double)0 << endl;
	cout << "0/0 = " << (sum * (long double)0.0) / (long double)0 << endl;
	cout << "LLONG_MAX = " << *find(v.begin(), v.end(), (long double)LLONG_MAX) << endl;
	cout << "Exista LLONG_MAX: " << (find(v.begin(), v.end(), (long double)LLONG_MAX) != v.end());
	cout<<" (TRUE)"<<endl;
	return 0;
}
