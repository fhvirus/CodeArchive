#include<iostream>
#include<cmath>
#include<iomanip>
#include<algorithm>
using namespace std;

int main(){
	int x, y, x1, y1, x2, y2, nx, ny;
	cin>>x>>y>>x1>>y1>>x2>>y2;
	if(x1 < x && x < x2)nx = 0;
	else nx = min(abs(x - x1), abs(x - x2));
	if(y1 < y && y < y2)ny = 0;
	else ny = min(abs(y - y1), abs(y - y2));
	cout<<setprecision(5)<<fixed<<sqrt(nx * nx + ny * ny);
	return 0;
}