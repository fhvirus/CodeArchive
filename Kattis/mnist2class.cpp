#include<iostream>
#include<sstream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	stringstream ss;
	ss << "-1	1	-1	1	-1	1	1	-1	-1	-1	-1	1	1	-1	-1	1	-1	1	-1	1	-1	-1	1	-1	1	-1	-1	-1	1	1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1	1	-1	-1	-1	-1";
	int a[51];
	for(int i= 0; i < 51; i++)ss>>a[i];
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 51; j++)
			cout<<-a[j]<<' ';
		cout<<'\n';
	}
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 51; j++)
			cout<<a[j]<<' ';
		cout<<'\n';
	}
	return 0;
}