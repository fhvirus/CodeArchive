#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int h,m,tmp;
	cin>>h>>m;
	tmp=(h*60+m-45+1440)%1440;
	cout<<tmp/60<<' '<<tmp%60;
	return 0;
}