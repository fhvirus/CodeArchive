#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1e5 + 1;
int n, a[N * 2], last[N];

// bit
int val[N];
void modify(int p, int v){
	for(; p <= n; p += p & -p) val[p] += v;
}
int query(int p){
	int ans = 0;
	for(; p > 0; p -= p & -p) ans += val[p];
	return ans;
}

int main(){
	cin >> n;
	for(int i = 0; i < n * 2; ++i)
		cin >> a[i];
	for(int i = 0; i <= n; ++i)
		last[i] = -1;
	for(int i = 0; i < n * 2; ++i){
		if(last[a[i]] == -1) last[a[i]] = query(a[i] - 1);
		else last[a[i]] = query(a[i] - 1) - last[a[i]];
		modify(a[i], 1);
	}
	long long ans = 0;
	for(int i = 1; i <= n; ++i)
		ans += last[i];
	cout << ans;
}