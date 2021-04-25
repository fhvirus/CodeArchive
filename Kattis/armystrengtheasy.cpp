#include<iostream>
#include<algorithm>
using namespace std;

int g[500],m[500],ng,nm,T,pg,pm;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>ng>>nm;
		for(int i=0;i<ng;i++)cin>>g[i];
		for(int i=0;i<nm;i++)cin>>m[i];
		sort(g,g+ng);
		sort(m,m+nm);
		pg=pm=0;
		while(pg<ng&&pm<nm){
			if(g[pg]<m[pm])pg++;
			else pm++;
		}
		if(pg==ng)cout<<"MechaGodzilla\n";
		else cout<<"Godzilla\n";
	}
	return 0;
}