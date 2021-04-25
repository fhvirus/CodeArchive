#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

#define justinlaiorz ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int t, n;

const int N = 31623;
vector<int> primes;
bool np[N];
inline void shai(){
	np[0] = np[1] = true;
	for(int i = 2; i < N; ++i){
		if(!np[i]) primes.push_back(i);
		for(int p: primes){
			if(i * p >= N) break;
			np[i * p] = true;
			if(i % p == 0) break;
		}
	}
}

inline vector<int> PF(int n){
	vector<int> ans;
	for(int i: primes){
		if(n % i == 0){
			ans.push_back(i);
			while(n > 0 and n % i == 0) n /= i;
		}
	}
	return ans;
}

int main(){ justinlaiorz
	shai();
	cin >> t;
	for(; t; --t){
		cin >> n;
		vector<int> pf = PF(n);
		if(pf.size() == 2 and n == pf[0] * pf[1]){
			cout << pf[0] << ' ' << pf[1] << ' ' << pf[0] * pf[1] << '\n' << 1 << '\n';
			continue;
		}
		// for(int i: pf) cout << i << ' ';
		// 	cout << '\n';
		vector<int> f;
		int i = 2;
		for(; i * i  < n; ++i)
			if(n % i == 0) f.push_back(i), f.push_back(n / i);
		if(n % i == 0) f.push_back(i);

		vector<vector<int>> jizz(pf.size());
		for(int j: f){
			for(int k = 0; k < pf.size(); ++k){
				if(j % pf[k] == 0){ jizz[k].push_back(j); break;} 
			}
		}

		for(int i = 0; i < pf.size(); ++i){
			for(int j = 0; j < jizz[i].size(); ++j){
				if(jizz[i][j] != n and i < pf.size() and jizz[i][j] != pf[i] * pf[i + 1])
					cout << jizz[i][j] << ' ';
			}
			if(i < pf.size() - 1)cout << pf[i] * pf[i + 1] << ' ';
		}
		cout << n << '\n' << 0 << '\n';

		// cout << pf[0];
	}
	return 0;
}