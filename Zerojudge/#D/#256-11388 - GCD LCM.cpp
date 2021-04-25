#include<iostream>
using namespace std;

int main(){
	int t,g,l;
	cin>>t;
	for(int i=0;i<t;i++){
		cin>>g>>l;
		if(l%g!=0){
			cout<<-1<<endl;
		} else {
			cout<<g<<' '<<l<<endl;
		}
	}
	return 0;
}