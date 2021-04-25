#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,s=0;
	cin>>n;
	while(n--){
		cin>>m;
		s+=(m<0?-m:0);
	}
	cout<<s;
	return 0;
}