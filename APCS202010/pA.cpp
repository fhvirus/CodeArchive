#include<iostream>
#include<algorithm>
using namespace std;

int a1, b1, c1, a2, b2, c2, n;

int main(){
	cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2 >> n;
	int ans = -2147483548;
	for(int i = 0; i <= n; ++i)
		ans = max(ans, a1 * i * i + b1 * i + c1 + a2 * (n - i) * (n - i) + b2 * (n - i) + c2);
	cout << ans;
}