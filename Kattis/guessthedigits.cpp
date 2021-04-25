#include<iostream>
#include<cmath>
using namespace std;

int m,n,p,q,nt,pt;

bool judge(int i){
	return (i%nt*pt+p)*q==i;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>m>>n>>p>>q;
	nt=pow(10,m-n);
	pt=pow(10,(int)log10(p*10));
	int mn=pow(10,m-1),mx=pow(10,m);
	for(int i=mn;i<mx;i++)if(judge(i)){cout<<i;return 0;}
	cout<<"IMPOSSIBLE";
	return 0;
}