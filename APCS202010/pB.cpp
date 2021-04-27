#include<iostream>
#include<algorithm>
using namespace std;

int r, c, k, m;
int a[52][52], b[52][52];

int main(){
	cin >> r >> c >> k >> m;
	for(int i = 0; i <= r + 1; ++i)
		for(int j = 0; j <= c + 1; ++j)
			a[i][j] = -1;
	for(int i = 1; i <= r; ++i)
		for(int j = 1; j <= c; ++j)
			cin >> a[i][j];
	for(int i = 1; i <= m; ++i){
		for(int i = 1; i <= r; ++i)
			for(int j = 1; j <= c; ++j){
				if(a[i][j] == -1){ b[i][j] = -1; continue;}
				b[i][j] = a[i][j];
				if(a[i+1][j] != -1){
					b[i][j] -= a[i][j] / k;
					b[i][j] += a[i+1][j] / k;
				}
				if(a[i-1][j] != -1){
					b[i][j] -= a[i][j] / k;
					b[i][j] += a[i-1][j] / k;
				}
				if(a[i][j+1] != -1){
					b[i][j] -= a[i][j] / k;
					b[i][j] += a[i][j+1] / k;
				}
				if(a[i][j-1] != -1){
					b[i][j] -= a[i][j] / k;
					b[i][j] += a[i][j-1] / k;
				}
			}
		for(int i = 1; i <= r; ++i)
			for(int j = 1; j <= c; ++j)
				a[i][j] = b[i][j];
	}
	int mn = 2147483647, mx = -2147483648;
	for(int i = 1; i <= r; ++i)
		for(int j = 1; j <= c; ++j)
			if(a[i][j] != -1) mn = min(mn, a[i][j]),
			mx = max(mx, a[i][j]);
	cout << mn << '\n' << mx;
}