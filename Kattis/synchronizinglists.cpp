#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	while(cin>>n&&n!=0){
		int a[n],b[n],c[n];
		for(int i=0;i<n;i++){
			cin>>a[i];
			b[i]=a[i];
		}
		for(int i=0;i<n;i++){
			cin>>c[i];
		}
		sort(b,b+n);
		sort(c,c+n);
		map<int,int> m;
		for(int i=0;i<n;i++){
			m[b[i]]=c[i];
		}
		for(int i=0;i<n;i++){
			cout<<m[a[i]]<<'\n';
		}
		cout<<'\n';
	}
	return 0;
}