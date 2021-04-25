#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	char a[n],b[m],tmp;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<m;i++)cin>>b[i];
	for(int i=m-1,j=n-1;i>=0;i--){
		tmp=(b[i]-a[j]+26)%26+97;
		b[i]=a[j];
		a[j]=tmp;
		if(j==0)j=n-1;
		else j--;
	}
	for(auto i:b)cout<<i;
	return 0;
}