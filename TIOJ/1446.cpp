#include<iostream>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int MAXN = 1e5;

string s[MAXN];

inline int calc(string a, string &b){
	long long f = 0, sa = a.size(), sb = b.size();
	while(f < sa and f < sb and a[f] == b[f]) ++f;
	return (sb - f) + (sa - f);
}

int main(){OW0
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i){
		cin >> s[i];
	}
	sort(s, s + n);
	long long ans = s[0].size() + s[n-1].size() + 1;
	for(int i = 1; i < n; ++i){
		ans += calc(s[i], s[i-1]) + 1;
	}
	cout << ans;
	return 0;
}