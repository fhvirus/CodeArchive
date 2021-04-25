#pragma GCC optimize("Ofast")
#include<iostream>
#include<string>
using namespace std;

const int N = 1e6 + 225;

int n, z[N*2], ans, len;
string in;
char s[N*2];

inline void manacher(){
	z[0] = 1;
	int l = 0, r = 0, m = 0;
	for(int i = 1; i <= n; ++i){
		if(i > r){
			m = i, l = m-1, r = m+1;
			while(l >= 0 and r < n and s[l] == s[r])
				--l, ++r;
			++l, --r;
			z[i] = (r - l) / 2 + 1;
		} else {
			if(i + z[m * 2 - i] - 1 > r)
				z[i] = r - i + 1;
			else if(i + z[m * 2 - i] - 1 < r)
				z[i] = z[m * 2 - i];
			else {
				m = i, l = m * 2 - r;
				while(l >= 0 and r < n and s[l] == s[r])
					--l, ++r;
				++l, --r;
				z[i] = (r - l) / 2 + 1;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	getline(cin, in);
	len = n = in.size();
	for(int i = 0; i < n; ++i)
		s[i * 2 + 1] = in[i];
	n = n * 2 + 1;
	manacher();
	for(int i = 0; i < n; ++i)
		if(z[i] + z[i + len] >= len) ++ans;
	cout << ans << ": ";
	for(int i = 0; i < n; ++i)
		if(z[i] + z[i + len] >= len) cout << i;
}