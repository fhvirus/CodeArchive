#include<iostream>
#include<algorithm>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){eek
	int T, n, a, b, c, d;
	cin >> T;
	while(T--){
		cin >> n >> a >> b >> c >> d;
		if((a+b)*n < c-d or (a-b)*n > c+d)
			cout << "No\n";
		else
			cout << "Yes\n";
	}
	return 0;
}