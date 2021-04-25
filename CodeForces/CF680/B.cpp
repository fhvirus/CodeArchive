#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t, a, b, c, d;
	cin >> t;
	while(t--){
		cin >> a >> b >> c >> d;
		cout << max(a + b, c + d) << '\n';
	}
	return 0;
}