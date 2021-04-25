#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,num,sum,prevnum;
	cin>>n;
	for(int i=0;i<n;i++){
		sum=0,prevnum=1;
		while(cin>>num&&num){
			if(num>prevnum*2)sum+=num-2*prevnum;
			prevnum=num;
		}
		cout<<sum<<endl;
	}
	return 0;
}