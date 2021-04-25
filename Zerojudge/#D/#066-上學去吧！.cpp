#include<iostream>
using namespace std;

int main(){
	int h,m;
	cin>>h>>m;
	cout<<((h*100+m)<730||(h*100+m)>=1700?"Off School":"At School")<<endl;
}