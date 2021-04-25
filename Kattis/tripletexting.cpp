#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string in;
	getline(cin, in);
	string a = in.substr(0, in.size()/3),
		   b = in.substr(in.size()/3, in.size()/3);
	if(a == b) cout << a;
	else cout << in.substr(in.size()/3*2, in.size()/3);
	return 0;
}