#include<iostream>
using namespace std;

int n;
long long ans;

int main(){
	cin >> n;
	for(int i = 2; i <= n; ++i){
		for(int j = 2; i * j <= n; ++j)
			ans += j;
	}
	cout << ans * 4;
}