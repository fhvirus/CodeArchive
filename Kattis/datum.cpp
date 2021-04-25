#include<iostream>
#include<string>
using namespace std;

int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
string days[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

int main(){
	int m,d,sumd=0;
	cin>>d>>m;
	for(int i=0;i<m-1;i++){
		sumd+=months[i];
	}
	sumd+=d+2;
	cout<<days[sumd%7];
	return 0;
}