#include<iostream>
#include<cmath>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,len;
	string in;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>in;
		len=sqrt(in.length());
		for(int j=0;j<len;j++){
			for(int k=0;k<len;k++){
				cout<<in[k*len+len-j-1];
			}
		}
		cout<<'\n';
	}
	return 0;
}