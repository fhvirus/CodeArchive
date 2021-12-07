#include<iostream>
using namespace std;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	string s;
	while(getline(cin, s)){
		int p = 0, n = s.size();
		while(p < n and s[p] == '0') ++p;
		if(p == n) break;
		bool a, b;
		a = b = ((s[n-1] - '0') & 1);
		if(p == n-1 and s[p] <= '3') b ^= 1;
		cout << (a ? "LOSE " : "WIN ") << (b ? "LOSE\n" : "WIN\n");
	}
}
