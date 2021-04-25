#include<iostream>
using namespace std;

const int N = 30000;
int n, m, a[N];

bool check(int d){
	int lastl = a[0], curd = 0, left = m;
	for(int i = 1; i < n; ++i){
		if(a[i] + a[i-1] > d) return false;
		curd += a[i];
		if(lastl + curd > d){
			if(left == 0) return false;
			lastl = curd, curd = 0, --left;
		}
	}
	return !(curd + a[0] > d and (left == 0 or a[n-1] + a[0] > d));
}

int main(){
	cin >> n >> m;
	m -= 2;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	int l = a[0] + a[n-1], r = 900000000, m;
	while(l < r){
		m = (l + r) / 2;
		cout << m << ' ' << check(m) << endl;
		if(check(m)) r = m;
		else l = m + 1;
	}
	cout << r;
	return 0;
}