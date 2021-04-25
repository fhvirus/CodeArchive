#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

#define int unsigned long long

void extgcd(int a, int b, int &x, int &y, int &d){
	if(!b){
		d = a;
		x = 1;
		y = 0;
		return;
	}
	extgcd(b, a%b, x, y, d);
	int newX = y, newY = x - a/b * y;
	x = newX, y = newY;
	return;
}

int modpow(int a, int b, int p){
	int tmp = a, ans = 1;
	for(int i = 0; (1<<i) <= b; i++){
		if((1<<i) & b) ans = ans * tmp % p;
		tmp = tmp * tmp % p;
	}
	return ans;
}

int money(int a, int m){
// 	static int x, y, d;
// 	extgcd(a, m, x, y, d);
// 	cout << a << ' ' << m << ' ' << x << ' ' << y << ' ' << d << '\n';
	return modpow(a, m-2, m);
}

signed main(){
	int n, tmp;
	string in;
	stringstream ss;
	vector<int> p, k, m;
	while(getline(cin, in)){
		// init for every testcase
		p.clear(); k.clear();
		ss.str(""); ss.clear();
		ss << in;
		while(ss >> tmp){
			p.push_back(tmp);
		}
		getline(cin, in);
		ss.str(""); ss.clear();
		ss << in;
		while(ss >> tmp){
			k.push_back(tmp);
		}

		int M = 1, ans = 0;
		for(auto i: p) M *= i;
		m.clear(); m.resize(p.size());
		for(int i = 0; i < m.size(); i++){
			m[i] = money(M/p[i], p[i]);
			//cout << p[i] << ' ' << M/p[i] << ' ' << m[i] << '\n';
		}

		for(int i = 0; i < k.size(); i++){
			ans += k[i] * m[i] * M/p[i];
		}
		cout << ans % M << '\n';
	}
	return 0;
}