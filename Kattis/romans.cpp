#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	double miles;
	cin>>miles;
	cout<<(int)(miles*1000*5280/4854+0.5)<<endl;
	return 0;
}