#include<iostream>
using namespace std;

int main(){
	int hands;
	char domsuit;
	cin>>hands>>domsuit;
	int sum=0;
	char num,suit;
	for(int i=0;i<4*hands;i++){
		cin>>num>>suit;
		if(num=='A')sum+=11;
		else if(num=='K')sum+=4;
		else if(num=='Q')sum+=3;
		else if(num=='J')if(suit==domsuit)sum+=20;else sum+=2;
		else if(num=='T')sum+=10;
		else if(num=='9'&&suit==domsuit)sum+=14;
	}
	cout<<sum;
	return 0;
}