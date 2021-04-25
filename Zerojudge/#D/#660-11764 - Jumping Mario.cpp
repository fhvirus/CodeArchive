#include<iostream>
using namespace std;

int main(){
	int t,n,h,l,tmp1,tmp2;
	cin>>t;
	for(int i=0;i<t;i++){
		cin>>n;
		cin>>tmp1;
		h=0;l=0;
		for(int j=0;j<n-1;j++){
			cin>>tmp2;
			if(tmp2>tmp1) h++;
			else if(tmp1>tmp2) l++;
			tmp1=tmp2;
		}
		cout<<"Case "<<i+1<<": "<<h<<' '<<l<<endl;
	}
	return 0;
}