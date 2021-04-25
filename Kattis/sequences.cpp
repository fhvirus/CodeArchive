#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int M = 1e9 + 7;

int main(){OW0
	string s;
	getline(cin, s);
	const int l = s.size();
	int i = 0, ans = 0, ones = 0, vars = 1;
	for(;i < l; i++){
		if(s[i] == '0'){
			ans += ones;
		} else if(s[i] == '1'){
			ones += vars;
		} else if(s[i] == '?'){
			ans  = ans * 2  % M + ones;
			ones = ones * 2 % M + vars;
			vars = vars * 2 % M;
		}
		ans %= M, ones %= M;
	}
	cout << ans << '\n';
	return 0;
}