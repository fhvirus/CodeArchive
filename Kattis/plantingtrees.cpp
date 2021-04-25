#include<iostream>
#include<algorithm>
using namespace std;

long long d[100000];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m = 0;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> d[i];
	}
	sort(d, d+n,[](int a, int b){return a>b;});
	for(int i = 0; i < n; i++){
		if(m < d[i] + i) m = d[i] + i;
	}
	cout << m+2;
	return 0;
}