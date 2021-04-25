#include<iostream>
#include<cmath>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,h,v;
	cin>>n>>h>>v;
	cout<<(n-h>h?n-h:h)*(n-v>v?n-v:v)*4;
	return 0;
}