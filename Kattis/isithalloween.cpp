#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string m;
	int d;
	cin>>m>>d;
	cout<<((m=="OCT"&&d==31)||(m=="DEC"&&d==25)?"yup\n":"nope\n");
	return 0;
}