#include<iostream>
#include<vector>
using namespace std;

#define int long long
const int N = 1e5 + 1;
vector<int> primes;
bool notprime[N];
void shai(){
	notprime[0] = notprime[1] = true;
	for(int i = 2; i < N; ++i){
		if(!notprime[i]) primes.push_back(i);
		for(int p: primes){
			if(i * p > N) break;
			notprime[i * p] = true;
			if(i % p == 0) break;
		}
	}
}

int n, in;
bool all0 = true, had = false;
int x = 1;
signed main(){
	cin >> n;
	shai();
	for(int p: primes){
		if(p * p > n) break;
		cout << "B " << p << '\n' << flush;
		cin >> in;
	}
	// if(all0){ cout << "C 1\n" << flush; return 0;}
	for(int p: primes){
		if(p * p > n) break;
		if(p * x > n) {cout << "C " << x << '\n' << flush; return 0;}
		cout << "B " << p << '\n' << flush;
		cin >> in;

		cout << " " << p << '\n' << flush;
		cin >> in;

		if(in > 0){
			int jizz = p;
			while(in > 0){
				x *= p, jizz *= p;
				if(jizz > n) break;
				cout << "B " << jizz << '\n' << flush;
				cin >> in;
			}
		}
	}
	// for(int p: primes){
	// 	if(p * p < n) continue;
	// 	if(p * x > n) break;
	// 	cout << "B " << p << '\n' << flush;
	// 	cin >> in;
	// 	cout << "A " << p << '\n' << flush;
	// 	cin >> in;
	// 	if(in > 0){ x *= p; break;}
	// }
	cout << "C " << x << '\n' << flush; return 0;
}