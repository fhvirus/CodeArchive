#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

double box(double x, double y){
	double h1 = ((x + y) + sqrt(x * x - x * y + y * y)) / 6;
	double h2 = ((x + y) - sqrt(x * x - x * y + y * y)) / 6;
	if(h1 < 0)return h2 * (x - 2 * h2) * (y - 2 * h2);
	else if(h2 < 0)return h1 * (x - 2 * h1) * (y - 2 * h1);
	return (h2 * (x - 2 * h2) * (y - 2 * h2) > h1 * (x - 2 * h1) * (y - 2 * h1)?
		h2 * (x - 2 * h2) * (y - 2 * h2):
		h1 * (x - 2 * h1) * (y - 2 * h1)
	);
}

int main(){
	int n;
	double x, y;
	cin>>n;
	for(int i =0; i < n; i++){
		cin>>x>>y;
		cout<<setprecision(10)<<fixed<<box(x,y)<<'\n';
	}
	return 0;
}
