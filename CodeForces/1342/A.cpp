#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	long long T, x, y, a, b;
	cin >> T;
	while(T--){
		cin >> x >> y >> a >> b;
		if((x^y) < 0){
			cout << abs(x-y) * a << '\n';
		} else {
			cout << min(min(abs(x), abs(y))*b + abs(x-y)*a, (abs(x)+abs(y))*a) << '\n';
		}
	}
	return 0;
}