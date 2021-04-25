#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int l,r;
	cin>>l>>r;
	if(!l&&!r)cout<<"Not a moose";
	else cout<<(l==r?"Even ":"Odd ")<<(l>r?l*2:r*2);
	return 0;
}