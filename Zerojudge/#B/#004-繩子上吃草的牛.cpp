#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main(){
	int a,b;
	while(cin>>a>>b){
		cout<<setiosflags(ios::fixed)<<setprecision(3)<<M_PI*b*sqrt((b+a)*(b-a))/4<<endl;
	}
	return 0;
}