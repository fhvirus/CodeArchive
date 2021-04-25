#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	int n;
	float m,p,x;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>m>>p;
		x=(p-m)*100/m;
		x+=(x>=0?1e-6:-1e-6);
		cout<<setiosflags(ios::fixed)<<setprecision(2)<<setw(6)<<x<<"% "
			<<(x>=10.00||x<=-7.00?"dispose":"keep")<<endl;
	}
	return 0;
}