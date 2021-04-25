#include<iostream>
using namespace std;

int main(){
	int T, n, ans[10];
	cin>>T;
	while(T--){
		cin>>n;
		if(n == 1){
			cout<<1<<'\n';
			continue;
		}
		for(int i=0;i<10;i++)ans[i]=0;
		for(int i = 9; i > 1; i--){
			while(n % i == 0){
				ans[i]++;
				n /= i;
			}
		}
		if(n > 1)cout<<-1;
		else for(int i = 1; i < 10; i++){
			for(int j = 0; j < ans[i]; j++){
				cout<<i;
			}
		}
		cout<<'\n';
	}
	return 0;
}