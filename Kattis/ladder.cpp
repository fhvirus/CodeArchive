#include<iostream>
#include<cmath>
using namespace std;

int main(){
	float h,v;
	cin>>h>>v;
	cout<<ceil(h/sin(v/180*3.14159265358979));
	return 0;
}