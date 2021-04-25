#include<iostream>
using namespace std;

int main(){
	char a[2];
	cout<<"十六進位表示法  相對應的十進位表示法"<<endl;
	while(cin>>a[0]>>a[1]){
		cout<<"      "<<a[0]<<a[1];
		cout<<"                 "<<(a[0]>64?a[0]-55:a[0]-48)*16+(a[1]>64?a[1]-55:a[1]-48)<<endl;
	}
	return 0;
}