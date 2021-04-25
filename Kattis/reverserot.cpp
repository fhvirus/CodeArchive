#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string a,b="ABCDEFGHIJKLMNOPQRSTUVWXYZ_.";
	int n;
	while(cin>>n&&n){
		cin>>a;
		for(int i=a.size()-1;i>=0;i--){
			cout<<b[(b.find(a[i])+n)%28];
		}
		cout<<'\n';
	}
	return 0;
}