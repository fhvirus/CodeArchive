#include<iostream>
using namespace std;

int main(){
	int s,t,n;
	cin>>s>>t>>n;
	int d[n+1],b[n],c[n];
	for(int i=0;i<n+1;i++)cin>>d[i];
	for(int i=0;i<n;i++)cin>>b[i];
	for(int i=0;i<n;i++)cin>>c[i];

	int ct=s;

	for(int i=0;i<n;i++){
		ct+=d[i];
		if(ct<=b[i]){
			ct=b[i];
		}else{
			ct=((ct-b[i])/c[i]+1)*c[i]+b[i];
		}
	}
	ct+=d[n];

	if(ct>t)cout<<"no";
	else cout<<"yes";

	return 0;
}