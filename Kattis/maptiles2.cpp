#include<iostream>
using namespace std;

int main(){
	string in;
	cin>>in;
	cout<<in.size()<<' ';
	int x=0, y=0;
	for(int i = 0; i < in.size(); i++){
		x += (in[i]=='1' || in[i]=='3');
		y += (in[i]=='2' || in[i]=='3');
		x <<= 1;
		y <<= 1;
	}
	cout<<x/2<<' '<<y/2;
	return 0;
}