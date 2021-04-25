#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	string a;
	cin>>n;
	while(n--){
		cin>>a;
		cout<<a.size()<<'\n';
	}
	return 0;
}