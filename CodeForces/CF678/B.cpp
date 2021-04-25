#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e5 + 1;
int t, n, a[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	vector<int> primes;
	vector<bool> np(N, false);
	np[0] = np[1] = true;
	for(int i = 2; i < N; ++i){
		if(!np[i]) primes.push_back(i);
		for(int p: primes){
			if(i * p >= N) break;
			np[i * p] = true;
			if(i % p == 0) break;
		}
	}
	cin >> t;
	for(; t; --t){
		cin >> n;
		int jiz;
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(j == i or j == i + 1 or (i == n-1 and j == 0))
					cout << "1 ";
				else 
					cout << "0 ";
			}
			cout << '\n';
		}
	}
	return 0;
}