#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	int t,n,m;
	cin>>t>>n>>m;
	int a[n],b[m];
	int i;
	bool f;
	for(int z=0;z<t;z++){
		for(i=0;i<n;i++)cin>>a[i];
		for(i=0;i<m;i++)cin>>b[i];
		f=0;
		for(i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(a[i]==b[j]&&i<n)i++;
			}
		}
		cout<<f<<i;
		if(i!=n-1)cout<<++i<<'\n';
		else cout<<1<<'\n';
	}
	return 0;
}