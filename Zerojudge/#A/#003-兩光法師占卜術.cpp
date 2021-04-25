#include<iostream>
using namespace std;

int main(){
	int M,D,S;
	while(cin>>M>>D){
		S=(M*2+D)%3;
		if(S==0) cout<<"普通"<<endl;
		else if(S==1) cout<<"吉"<<endl;
		else cout<<"大吉"<<endl;
	}
	return 0;
}