#include<iostream>
#include<iomanip>
#include<utility>
#include<cmath>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define F first
#define S second

int main(){OW0
	pair<double, double> p[9];
	int n;
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			cin>>n;
			p[n-1] = {x, y};
		}
	}
	double ans = 0;
	for(int i = 0; i < 8; i++){
		ans += sqrt((p[i+1].F - p[i].F) * (p[i+1].F - p[i].F) +
					(p[i+1].S - p[i].S) * (p[i+1].S - p[i].S));
	}
	cout<<setprecision(10)<<fixed<<ans;
	return 0;
}