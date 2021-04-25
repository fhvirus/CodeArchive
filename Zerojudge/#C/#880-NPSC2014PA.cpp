#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	int n;
	float AB,H,BB,HBP,TB,SF,OPS;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>AB>>H>>BB>>HBP>>TB>>SF;
		cout<<setprecision(3)<<fixed<<(AB*(H+BB+HBP)+TB*(AB+BB+SF+HBP))/(AB*(AB+BB+SF+HBP))<<'\n';
	}
	return 0;
}