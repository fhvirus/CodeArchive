#include<iostream>
using namespace std;

inline int solve(int n, int k){
	int ans = 0;
	for(int i = 2; i <= n;){
		if(ans + k >= i){
			ans = (ans + k) % i;
			++i;
			continue;
		}
		int step = (i - 1 - ans - 1) / (k - 1);
		if(i + step > n){
			ans += (n - (i - 1)) * k;
			break;
		}
		i += step;
		ans += step * k;
	}
	return ans;
}

int main(){
	int n, k;
	cin >> n >> k;
	for(int i = 2; i <= 30000; ++i){
		if(solve(n, i) == k - 1){ cout << i; return 0;}
	}
	cout << 0;
}