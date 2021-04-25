#include<iostream>
#include<cmath>
using namespace std;

double deg(double a){return a*3.1415926535/180;}

int main(){
	double v,a,x,h1,h2,t,y;
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>v>>a>>x>>h1>>h2;
		t=x/v/cos(deg(a));
		y=v*t*sin(deg(a))-0.5*9.81*t*t;
		cout<<(h1+1<y&&y<h2-1?"Safe\n":"Not Safe\n");
	}
	return 0;
}