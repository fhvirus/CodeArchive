#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

constexpr int MAXN = 50000;

vector<bool> isPrime(MAXN+1, true);
vector<int> primes;
void sieve(){
	for(int i = 2; i <= MAXN; i++){
		if(isPrime[i]) primes.push_back(i);
		for(auto p: primes){
			if(i*p > MAXN) break;
			isPrime[i*p] = false;
			if(!(i%p)) break;
		}
	}
}


bool shai[200005];
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	sieve();
	int T, l, r, ans, mult;
	bool yn;
	cin >> T;
	while(T--){
		cin >> l >> r;
		ans = 0;
		for(int i = 0; i<=r-l; i++)shai[i]=true;
		for(auto i: primes){
			if(i > r) break;
			mult = max(l/i + (l%i? 1:0), 2);
			for(; i*mult <= r; mult++){
				//cout << i*mult << ' ';
				shai[i*mult-l] = false;
			}
		}
		//cout << '\n';
		for(int i = 0; i <= r-l; i++){
			//cout << i+l << ' ' << shai[i] << '\n';
			ans += shai[i];
		}
		cout << ans << '\n';
	}

	return 0;
}