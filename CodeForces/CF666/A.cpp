#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int t, n, cnt[26];
string in;

int main(){OW0
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 0; i < 26; ++i) cnt[i] = 0;
		for(int i = 0; i < n; ++i){
			cin >> in;
			for(char s: in) cnt[s - 'a']++;
		}
		bool ans = true;
		for(int i = 0; i < 26; ++i)
			if(cnt[i] % n != 0){ans = false; break;}
		cout << (ans ? "YES" : "NO") << '\n';
	}
}