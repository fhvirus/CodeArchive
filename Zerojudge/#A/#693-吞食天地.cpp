#include<iostream>
using namespace std;

int main(){
	int n,m,l,r;
	while(cin>>n>>m){
		int a[n],tmp;
		for(int i=0;i<n;i++){
			cin>>tmp;
			a[i]=((i==0)?tmp:a[i-1]+tmp);
		}
		for(int i=0;i<m;i++){
			cin>>l>>r;
			cout<<a[r-1]-(l==1?0:a[l-2])<<'\n';
		}
	}
	return 0;
}