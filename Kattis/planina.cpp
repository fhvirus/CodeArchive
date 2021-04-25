#include<iostream>
#include<cmath>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int a;
	cin>>a;
	cout<<(int)pow(4,a)+(int)pow(2,a+1)+1<<endl;
	return 0;
}