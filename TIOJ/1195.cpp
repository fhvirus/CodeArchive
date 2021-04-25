#include<iostream>
using namespace std;

int main(){
	int n, ans = 0;
	string in;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for(cin >> n; n; --n){
		cin >> in;
		if(in[2] == in[3] and in[3] == in[4]){
			if(in[4] == in[5]) ans += 2000;
			else ans += 1000;
		}
		else if(in[3] == in[4] and in[4] == in[5]) ans += 1000;
		else if(in[2] == in[3] and in[4] == in[5]) ans += 1500;
	}
	cout << ans;
	return 0;
}