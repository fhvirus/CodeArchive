#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main(){
	double x1,x2,y1,y2,p;
	while(cin>>x1&&x1!=0){
		cin>>y1>>x2>>y2>>p;
		cout<<setprecision(10)<<fixed<<pow(pow(abs(x2-x1),p)+pow(abs(y2-y1),p),1/p)<<'\n';
	}
	return 0;
}