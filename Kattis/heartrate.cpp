#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,b;
	double p;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>b>>p;
		cout<<(b-1)*60.0/p<<' '<<b*60.0/p<<' '<<(b+1)*60.0/p<<'\n';
	}
	return 0;
}