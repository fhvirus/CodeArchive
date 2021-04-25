#pragma GCC optimize("Ofast")
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<utility>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define ff first
#define ss second
#define For(i,n) for(int i=0;i<n;++i)

const int N = 1e5 + 225;
int m, n, p, a[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> m >> p >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	a[++n] = p;
	int eek = m, ans = 0;
	for(int i = 1; i <= n; ++i){
		if(eek >= a[i]) continue;
		if(a[i] - a[i-1] > m){
			cout << "IMPOSSIBLE";
			return 0;
		}
		++ans;
		eek = a[i-1] + m;
	}
	cout << ans;
	return 0;
}
