#include<iostream>
#include<vector>
using namespace std;

bool isntprime[65536];
vector<int> primes;

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	//linear sieve
	isntprime[0]=1,isntprime[1]=1;
	for(int i=2;i<65536;i++){
		if(!isntprime[i])primes.push_back(i);
		for(int p:primes){
			if(i*p>65536)break;
			isntprime[i*p]=1;
			if(!(i%p))break;
		}
	}
	int n,m;
	bool isprime;
	cin>>m;
	for(int i=0;i<m;i++){
		cin>>n;
		isprime=0;
		for(int p:primes){
			if(n==p){
				isprime=1;
				break;
			}
		}
		cout<<(isprime?"Y\n":"N\n");
	}
	return 0;
}