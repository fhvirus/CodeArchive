#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string in;
	getline(cin, in);
	int b, w;
	b = w = 0;
	for(auto i: in){
		if(i == 'W') w++;
		else b++;
	}
	cout << (b==w);
	return 0;
}