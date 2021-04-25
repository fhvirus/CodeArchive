#include<iostream>
#include<vector>
using namespace std;

bool isntprime[46350];
vector<int> primes;

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	//linear sieve
	isntprime[0]=1,isntprime[1]=1;
	for(int i=2;i<46350;i++){
		if(!isntprime[i])primes.push_back(i);
		for(int p:primes){
			if(i*p>46350)break;
			isntprime[i*p]=1;
			if(!(i%p))break;
		}
	}
	int n;
	bool isprime;
	while(cin>>n){
		if(n>46350){
			isprime=1;
			for(int p:primes){
				if(!(n%p)){
					isprime=0;
					break;
				}
			}
		}else{
			isprime=0;
			for(int p:primes){
				if(n==p){
					isprime=1;
					break;
				}
			}
		}
		cout<<(isprime?"質數\n":"非質數\n");
	}
	return 0;
}