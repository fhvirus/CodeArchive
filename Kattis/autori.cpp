#include<iostream>
#include<istream>
using namespace std;

int main(){
	char a[100];
	while(cin.getline(a,100,'-')){
		cout<<a[0];
	}
	return 0;
}