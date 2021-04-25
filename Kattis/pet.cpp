#include<iostream>
using namespace std;

int main(){
	int sum,maxsum=0,num=0,in;
	for(int i=0;i<5;i++){
		sum=0;
		for(int j=0;j<4;j++){
			cin>>in;
			sum+=in;
		}
		if(sum>maxsum){
			maxsum=sum;
			num=i+1;
		}
	}
	cout<<num<<' '<<maxsum;
	return 0;
}