#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main(){
	double a,b,d;
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>d;
		if(d*d-4*d>=0){
			cout<<"Y ";
			a=(d+sqrt(d*d-4*d))/2;
			b=(d-sqrt(d*d-4*d))/2;
			cout<<setprecision(9)<<fixed<<a<<' '<<b<<'\n';
		} else {
			cout<<"N\n";
		}
	}
	return 0;
}