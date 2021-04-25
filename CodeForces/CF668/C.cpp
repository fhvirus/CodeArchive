#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<iostream>
#include<string>
using namespace std;

int t, n, k;
string in;

int main(){
	cin >> t;
	for(; t; --t){
		cin >> n >> k >> in;
		bool ans = true;
		int zero = 0, one = 0;
		for(int i = 0; i < k; ++i){
			int jizz = -1;
			for(int j = i; j < n; j += k){
				if(in[j] != '?'){
					if(jizz != -1 and in[j] - '0' != jizz){
						ans = false;
						break;
					}
					jizz = in[j] - '0';
				}
			}
			if(jizz != -1) (jizz == 1 ? one : zero)++;
		}
		if(zero > k/2 or one > k/2) ans = false;
		cout << (ans ? "YES" : "NO") << '\n';
	}
}