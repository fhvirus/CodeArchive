#include<iostream>
using namespace std;

int main(){
	int mom,jin,budget[12],i;
	bool a;
	while(cin>>budget[0]){
		for(i=0;i<11;i++) cin>>budget[i+1];
		jin=0;mom=0;a=true;
		for(i=0;i<12;i++){
			jin+=300-budget[i];
			if(jin<0){
				cout<<-i-1<<endl;
				a=false;
				break;
			}
			while(jin>100){
				jin-=100;
				mom+=100;
			}
		}
		if(a){
			cout<<jin+mom*1.2<<endl;
		}
	}
}