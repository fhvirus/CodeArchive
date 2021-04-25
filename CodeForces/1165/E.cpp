#include<iostream>
#include<algorithm>
using namespace std;

#define MAXN 200005
#define MODN 998244353
typedef unsigned long long int ulli;

ulli a[MAXN], b[MAXN];

bool cmp(int x, int y){
	return x > y;
}

int main(){
	ulli n;
	cin>>n;
	for(ulli i = 0; i < n; i++){
		cin >> a[i];
		a[i] *= (i+1) * (n-i);
	}
	for(ulli i = 0; i < n; i++){
		cin >> b[i];
	}
	sort(a, a + n);
	sort(b, b + n, cmp);
	ulli ans = 0;
	for(ulli i = 0; i < n; i++){
		ans = (ans + (a[i]%MODN) * (b[i]%MODN) % MODN)% MODN;
	}
	cout << ans;
	return 0;
}