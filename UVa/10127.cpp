#include<iostream>
using namespace std;

int main(){
	int n,m,cnt;
	while(cin>>n){
		cnt=1;
		m=1;
		while(m%n){
			m=(m%n)*10+1;cnt++;
		}
		cout<<cnt<<'\n';
	}
	return 0;
}