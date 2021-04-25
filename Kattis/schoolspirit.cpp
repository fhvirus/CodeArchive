#include<iostream>
#include<algorithm>
#include<cmath>
#include<iomanip>
using namespace std;

#define owo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

double a[50], g[50];

int main(){owo
	int n;
	cin>>n;
	for(int i = 0; i < n; i++)cin>>a[i];
	sort(a, a+n, [](int x, int y){return x>y;});
	for(int i = 0; i < n; i++){
		g[i] = a[i]*pow(0.8, i-1);
		a[i] *= pow(0.8, i);
	}
	for(int i = 1; i < n; i++){
		a[i]+=a[i-1];
		g[n-i-1]+=g[n-i];
	}
	double tmp = 0;
	for(int i = 0; i < n; i++){
		if(i > 0)tmp += a[i-1];
		if(i < n-1) tmp += g[i+1];
	}
	cout<< setprecision(6) <<fixed
		<< a[n-1]/5 <<'\n'
		<< tmp/n/5 <<'\n';
	return 0;
}