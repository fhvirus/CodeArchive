#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string a,b;
	cin>>a>>b;
	cout<<(a.size()>=b.size()?"go":"no");
	return 0;
}