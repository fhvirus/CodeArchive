#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int x,y;
	cin>>x>>y;
	cout<<(x>0?(y>0?1:4):(y>0?2:3))<<endl;
	return 0;
}