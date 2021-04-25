#include<iostream>
using namespace std;

int main(){
	int n, k[100], ans = 1;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> k[i];
		if(i>0 and k[i] < k[i-1])
			ans++;
	}
	cout << ans;
	return 0;
}