#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int x,y,n;
	cin>>x>>y>>n;
	for(int i=1;i<=n;i++){
		if(i%x){
			if(i%y)cout<<i<<'\n';
			else cout<<"Buzz\n";
		}else{
			if(i%y)cout<<"Fizz\n";
			else cout<<"FizzBuzz\n";
		}
	}
	return 0;
}