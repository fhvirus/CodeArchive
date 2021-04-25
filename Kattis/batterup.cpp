#include<iostream>
using namespace std;

int main(){
	int n;
	double in,cnt=0,sum=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>in;
		if(in!=-1){
			cnt+=1;
			sum+=in;
		}
	}
	cout<<sum/cnt;
	return 0;
}