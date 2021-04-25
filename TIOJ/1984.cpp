#include<iostream>
#include<cmath>
#include<string>
using namespace std;

int main(){
	int t;
	cin >> t;// cin.ignore();
	string s;
	for(; t; --t){
		// getline(cin, s);
		// if(s == "1"){ cout << 0 << endl; continue;}
		// long double ans = (s.size() - 1) * log2l(10);
		// long double a = 0, times = 1;
		// for(int i = 0; i < s.size() and i < 18; ++i)
		// 	a += (s[i] - '0') * times, times *= .1;
		// ans += log2l(a - times);
		// cout << ceill(ans) << endl;
		long long n;
		cin >> n;
		// if(n == 1){ cout << 0 << endl; continue;}
		cout << 63 - __builtin_clzll(n) << endl;
	}
}