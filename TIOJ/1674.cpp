#pragma Ofast
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
#pragma loop-opt(on)
#include<iostream>
using namespace std;
#define ll long long
#define M 1000000009
ll N, i = 1, n;
__int128 sum, r, l, jizz, s, last;
int main(){
	cin >> N; n = N; r = n;
	for(; i * i <= n; ++i){
		l = (n / (i + 1) + 1);
		sum += i * r;
		if(l != i) jizz = (r + l) * (r - l + 1) >>1, sum += jizz * i;
		r = l - 1;
	}
	s = (__int128)n * n;
	N = (s - sum) % M;
	cout << N;
}