#pragma Ofast
#pragma loop-opt(on)
#pragma GCC target("avx2")
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
const int N = 10001;
int kmp[N];
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t;
	cin >> t;
	cin.ignore();
	for(; t; --t){
		string s;
		// cin >> s;
		getline(cin, s);
		int q;
		cin >> q;
		cin.ignore();
		for(; q; --q){
			string w;
			// cin >> w;
			getline(cin, w);
			int ws = w.size(), ss = s.size(), ans = 0;
			kmp[0] = 0;
			for(int i = 1; i < ws; ++i){
				kmp[i] = kmp[i-1];
				while(w[i] != w[kmp[i]]){
					if(kmp[i] == 0){
						kmp[i] = -1;
						break;
					}
					kmp[i] = kmp[kmp[i] - 1];
				}
				++kmp[i];
			}
			for(int m = 0, i = 0; m < ss - ws + 1; ){
				while(i < ws and w[i] == s[m + i]) ++i;
				--i;
				if(i == ws - 1) ++ans;
				if(i == -1){
					++m;
					i = 0;
				} else {
					m = m + i - kmp[i] + 1;
					i = kmp[i];
				}
			}
			cout << ans << '\n';
		}
	}
}