#include<iostream>
using namespace std;
long long pow(long long x, long long e){
	long long ans = 1;
	while(e) (e & 1) and (ans = ans * x % 1000000007), x = x * x % 1000000007, e >>= 1;
	return ans;
}
int main(){
	long long n, m, k;
	cin >> n >> m >> k;
	cout << (((n ^ m) & 1) and k == -1 ? 0 : pow(pow(2, n-1), (m-1)));
}